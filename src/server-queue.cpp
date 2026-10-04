#include <algorithm>
#include <cassert>
#include <condition_variable>
#include <deque>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <utility>
#include <vector>

std::mutex log_mutex;

void trace(const char * message, int id = -1) {
    std::lock_guard<std::mutex> lock(log_mutex);
    std::cout << "thread " << std::this_thread::get_id() << " | " << message;
    if (id >= 0) {
        std::cout << " | id=" << id;
    }
    std::cout << '\n';
}

enum class task_type {
    decision,
    next_response,
    stop
};

struct task {
    task_type type;
    int id;
    int index;
    int steps;
};

struct result {
    int id;
    int index;
    double score;
};

class task_queue {
private:
    std::mutex              mutex;
    std::condition_variable condition;
    std::deque<task>        pending;

public:
    void post(task task) {
        std::unique_lock<std::mutex> lock(mutex);
        pending.push_back(std::move(task));
        trace("task queued", pending.back().id);

        // The OS is signaled via futex and the kernel picks one thread from the
        // conditional variables wait queue and moves it back to the runnable queue.
        condition.notify_one();
    }

    void run(const std::function<void(task)> & on_task,
             const std::function<void()> & update_slots) {
        for (;;) {
            // lock the mutex using unique_lock and not lock_guard as we need
            // to be able to unlock before calling on_task.
            std::unique_lock<std::mutex> lock(mutex);
            trace("server checks task predicate");

            // wait until there is a pending task.
            // Thread enters wait state:
            // if predicates == true keep lock an proceed
            // if predicates == false:
            // Register thread on CV wait list
            // Release the mutex (lock.unlock().
            // Deschedule thread (sleep in kernel via futex (Fast Userspace Mutex))
            // ...
            // Wakeup via notify_one() or notify_all()
            // Re-aquire the mutex (blocks until lock is secured)
            // Re-evaluate predicate (still false then repeat the above steps)
            // otherwise if true then continue with the mutex locked.
            condition.wait(lock, [&] {
                    return !pending.empty();
            });

            while (!pending.empty()) {
                task task = std::move(pending.front());
                pending.pop_front();

                // Callbacks may post more tasks to this same queue. This does
                // not happed for this example but if a callback call tasks.post
                // it would try to lock the same mutex again::
                // std::unique_lock<std::mutex> lock(mutex);
                // This would cause a deadlock.
                lock.unlock();
                if (task.type == task_type::stop) {
                    trace("server stops");
                    return;
                }
                // call on_task callback.
                on_task(std::move(task));
                lock.lock();
            }
            lock.unlock();

            // call update_slots callback.
            update_slots();
        }
    }
};

class result_queue {
private:
    std::mutex mutex;
    std::condition_variable condition;
    std::deque<result> pending;

public:

    void send(result result) {
        std::unique_lock<std::mutex> lock(mutex);
        pending.push_back(std::move(result));
        trace("result queued", pending.back().id);

        condition.notify_one();
    }

    result receive() {
        std::unique_lock<std::mutex> lock(mutex);
        trace("handler checks result predicate");

        // waits for the results to become available.
        condition.wait(lock, [&] { return !pending.empty(); });

        result result = std::move(pending.front());
        pending.pop_front();

        return result;
    }

};

class response_reader {
private:
    task_queue   & tasks;
    result_queue & results;
    std::size_t count = 0;

public:
    response_reader(task_queue & tasks, result_queue & results) : tasks(tasks), results(results) {}

    void post_tasks(std::vector<task> input) {
        count = input.size();
        for (std::size_t i = 0; i < input.size(); ++i) {
            input[i].index = static_cast<int>(i);
            tasks.post(std::move(input[i]));
        }
    }

    std::vector<result> wait_for_all() {
        std::vector<result> ordered(count);
        for (std::size_t i = 0; i < count; ++i) {
            result result = results.receive();
            trace("handler received result", result.id);
            ordered.at(result.index) = result;
        }
        return ordered;
    }
};

struct slot {
    struct task task;
    int remaining;
};

class server {
private:
    std::vector<slot> slots;

public:
    task_queue   tasks;
    result_queue results;

    void process_single_task(task task) {
        if (task.type == task_type::decision) {
            trace("server assigns task to slot", task.id);
            slots.push_back({task, task.steps});
        }
    }

    void update_slots() {
        if (slots.empty()) {
            return;
        }

        // Keep the loop running even if no new request arrives.
        tasks.post({task_type::next_response, -1, -1, 0});
        trace("server evaluates one batch");

        for (slot & slot : slots) {
            --slot.remaining; // Simulated inference; no sleeps or model required.
            if (slot.remaining == 0) {
                // this will cause send to add the result to the result_queue's pending
                // deque.
                results.send({slot.task.id, slot.task.index, slot.task.id / 100.0});
            }
        }
        slots.erase(std::remove_if(slots.begin(), slots.end(),
                    [](const slot & slot) { return slot.remaining == 0; }), slots.end());
    }

};

void handle_request(server & server) {
    trace("HTTP handler starts");
    // Create a response reader which is the has access to the server tasks which
    // is the task_queue.
    response_reader rd(server.tasks, server.results);

    rd.post_tasks({
        {task_type::decision, 10, -1, 3},
        {task_type::decision, 20, -1, 1},
        {task_type::decision, 30, -1, 2},
    });

    const auto answers = rd.wait_for_all();

    assert(answers.size() == 3);
    for (std::size_t i = 0; i < answers.size(); ++i) {
        assert(answers[i].id == static_cast<int>((i + 1) * 10));
        trace("HTTP response includes answer", answers[i].id);
    }
    server.tasks.post({task_type::stop, -1, -1, 0});
}

int main() {
    server server;
    trace("main thread is the server thread");

    // create a new thread with the function handle_request and pass the server
    // object as a reference.
    std::thread http_thread(handle_request, std::ref(server));

    // this following will run task_queue's run function taking the on_task callback
    // and the update_slots callback.
    server.tasks.run(
        [&](task task) { server.process_single_task(std::move(task)); },
        [&] { server.update_slots(); });

    http_thread.join();

    trace("handler joined; safe to destroy queues");
}

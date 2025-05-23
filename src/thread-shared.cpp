#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>

struct SharedData {
    int counter = 0;
    std::mutex counter_mutex;
    
    void increment() {
        std::lock_guard<std::mutex> lock(counter_mutex);
        ++counter;
        std::cout << "Counter incremented to: " << counter << " (Thread ID: " << std::this_thread::get_id() << ")\n";
    }
    
    int get_counter() {
        std::lock_guard<std::mutex> lock(counter_mutex);
        return counter;
    }
};

void worker_thread(SharedData & data, int thread_num, int iterations) {
    std::cout << "Thread " << thread_num << " starting...\n";
    for (int i = 0; i < iterations; ++i) {
        // Do some work
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // Safely modify shared data
        data.increment();
    }
    std::cout << "Thread " << thread_num << " finished.\n";
}

int main() {
    std::cout << "=== C++ Concurrent Programming Example ===\n\n";
    SharedData shared_data;
    std::thread thread1(worker_thread, std::ref(shared_data), 1, 5);
    std::thread thread2(worker_thread, std::ref(shared_data), 2, 5);
    std::cout << "Both threads started. Main thread waiting...\n\n";
    
    thread1.join();
    thread2.join();
    
    std::cout << "\nBoth threads completed.\n";
    std::cout << "Final counter value: " << shared_data.get_counter() << "\n";
    
    return 0;
}

/*
THINGS TO EXPERIMENT WITH:
1. Remove the mutex and see what happens (race conditions!)
2. Try different sleep durations
3. Add more threads
4. Try std::atomic<int> instead of mutex for simple counters
5. Experiment with different locking strategies

ALTERNATIVE APPROACHES:
- Use std::atomic<int> for simple counters (lock-free)
- Use std::shared_mutex for reader-writer scenarios
- Use std::condition_variable for thread communication
*/

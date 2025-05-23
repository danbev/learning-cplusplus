#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <queue>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> data_queue;
bool finished = false;

void producer() {
    for (int i = 1; i <= 5; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        
        {
            std::lock_guard<std::mutex> lock(mtx);
            data_queue.push(i);
            std::cout << "Produced: " << i << std::endl;
        }
        
        // Wake up waiting consumer
        cv.notify_one();
    }
    
    // Signal we're done
    {
        std::lock_guard<std::mutex> lock(mtx);
        finished = true;
    }
    cv.notify_one();
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx); // locks the mutex
        std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
        
        // Wait until there's data or we're finished
        // cv.wait unlocks while sleeping, then when it is notificed it will
        // relock the mutex.
        cv.wait(lock, []{ return !data_queue.empty() || finished; });
        
        // Process all available data
        while (!data_queue.empty()) {
            int item = data_queue.front();
            data_queue.pop();
            std::cout << "Consumed: " << item << std::endl;
        }
        
        if (finished) break;
    }
}

int main() {
    std::cout << "Starting producer-consumer example\n";
    
    std::thread prod(producer);
    std::thread cons(consumer);
    
    prod.join();
    cons.join();
    
    std::cout << "Done!\n";
    return 0;
}

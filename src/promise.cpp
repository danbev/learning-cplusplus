#include <iostream>
#include <future>
#include <thread>

void worker_with_promise(std::promise<int> prom, int x) {
    std::cout << "Worker computing " << x << " on thread: " << std::this_thread::get_id() << std::endl;
    
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
    int result = x * x;
    
    // Manually set the result
    prom.set_value(result);
    
    std::cout << "Worker finished, result sent\n";
}

int main() {
    std::cout << "Main thread: " << std::this_thread::get_id() << std::endl;
    
    // Create a promise
    std::promise<int> promise;
    
    // Get the future BEFORE starting work
    std::future<int> result = promise.get_future();
    
    std::cout << "\nPromise created, starting worker thread\n";
    
    // Start worker thread (must move the promise)
    std::thread worker(worker_with_promise, std::move(promise), 5);
    
    std::cout << "Worker started, doing other work in main...\n";
    
    // Get the result (blocks until promise.set_value() called)
    std::cout << "Result: " << result.get() << std::endl;
    
    worker.join();
    
    return 0;
}

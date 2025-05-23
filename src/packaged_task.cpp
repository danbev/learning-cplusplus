#include <iostream>
#include <future>
#include <thread>

int compute_something(int x) {
    std::cout << "Computing " << x << " on thread: " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    return x * x;
}

int main() {
    std::cout << "Main thread: " << std::this_thread::get_id() << std::endl;
    
    // Create a packaged_task
    std::packaged_task<int(int)> task(compute_something);
    
    // Get the future BEFORE running the task
    std::future<int> result = task.get_future();
    
    std::cout << "\nTask created, but not executed yet\n";
    
    // Now we can run it in different ways:
    
    // Option 1: Run in current thread
    // task(5);  // Executes immediately
    
    // Option 2: Run in separate thread
    std::thread worker(std::move(task), 5);
    
    std::cout << "Task started in separate thread\n";
    std::cout << "Doing other work in main thread...\n";
    
    // Get the result (blocks until task completes)
    std::cout << "Result: " << result.get() << std::endl;
    
    worker.join();
    
    return 0;
}

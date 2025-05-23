#include <iostream>
#include <thread>
#include <mutex>
#include <functional>

struct SharedData {
    int value = 42;
    std::mutex mtx;
    
    void print_address() {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "SharedData object address: " << this << std::endl;
    }
};

// Simulate what std::thread does internally
template<typename Function, typename... Args>
class SimpleThread {
private:
    // This is similar to what std::thread stores internally
    std::function<void()> stored_function;
    pthread_t native_handle;
    
    // Static function that pthread_create can call
    static void* thread_entry_point(void* arg) {
        // Cast back to our stored function and execute it
        auto* func = static_cast<std::function<void()>*>(arg);
        (*func)();
        return nullptr;
    }
    
public:
    template<typename F, typename... A>
    SimpleThread(F&& func, A&&... args) {
        // This is the KEY PART: std::thread stores a COPY of the callable
        // and all arguments. It uses perfect forwarding to preserve value categories.
        
        // Create a bound function that captures all arguments BY VALUE (unless std::ref)
        stored_function = std::bind(std::forward<F>(func), std::forward<A>(args)...);
        
        // Now create the actual pthread
        int result = pthread_create(&native_handle, nullptr, thread_entry_point, &stored_function);
        if (result != 0) {
            throw std::runtime_error("Failed to create thread");
        }
    }
    
    void join() {
        pthread_join(native_handle, nullptr);
    }
};

int main() {
    SimpleThread thread([](SharedData& data) {
        data.print_address();
    }, std::ref(SharedData()));
    
    return 0;
}

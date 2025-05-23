#include <iostream>
#include <mutex>
#include <shared_mutex>

std::mutex mtx;
std::shared_mutex shared_mtx;

int main() {
    std::cout << "=== C++ Lock Types ===\n\n";
    
    // 1. lock_guard - Simple, automatic
    {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "lock_guard: Locks on creation, unlocks on destruction\n";
        // Cannot unlock manually, cannot relock
    }
    
    // 2. unique_lock - Flexible, manual control
    {
        std::unique_lock<std::mutex> lock(mtx);
        std::cout << "unique_lock: Can unlock/relock manually\n";
        lock.unlock();
        std::cout << "Unlocked manually\n";
        lock.lock();
        std::cout << "Locked again\n";
    }
    
    // 3. shared_lock - Multiple readers
    {
        std::shared_lock<std::shared_mutex> lock(shared_mtx);
        std::cout << "shared_lock: Multiple readers can hold this simultaneously\n";
    }
    
    // 4. scoped_lock - Multiple mutexes (C++17)
    std::mutex mtx2;
    {
        std::scoped_lock lock(mtx, mtx2);  // Locks both, avoids deadlock
        std::cout << "scoped_lock: Locks multiple mutexes safely\n";
    }
    
    return 0;
}

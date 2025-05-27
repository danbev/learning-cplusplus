#include <iostream>
#include <utility>

class Test {
public:
    Test(int x) : value(x) {
        std::cout << "Constructor: " << value << std::endl;
    }
    
    Test(const Test& other) : value(other.value) {
        std::cout << "Copy constructor: " << value << std::endl;
    }
    
    Test(Test&& other) : value(other.value) {
        std::cout << "Move constructor: " << value << std::endl;
    }
    
    int value;
};

// Without perfect forwarding - always copies/moves everything
template<typename T, typename... Args>
T* make_bad(Args... args) {
    return new T(args...);  // Always copies args
}

// With perfect forwarding - preserves value categories
template<typename T, typename... Args>
T* make_good(Args&&... args) {
    return new T(std::forward<Args>(args)...);
}

int main() {
    std::cout << "=== Without perfect forwarding ===" << std::endl;
    Test original(18); // first constructor call


    // One copy because the function takes Args and not Args&&. And then another
    // copy we creating the new T object on the heap
    Test * bad = make_bad<Test>(original);
    delete bad;
    
    std::cout << "\n=== With perfect forwarding ===" << std::endl;
    Test original2(99);
    Test * good = make_good<Test>(original2);  // One copy
    delete good;
    
    /*
    std::cout << "\n=== Moving with perfect forwarding ===" << std::endl;
    Test * moved = make_good<Test>(Test(123));  // Can move temporary objects
    delete moved;
    */
    
    return 0;
}

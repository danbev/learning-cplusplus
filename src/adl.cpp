#include <iostream>

namespace custom_namespace {
    struct custom_type {};
    
    void print(custom_type) {
        std::cout << "Hello from custom_namespace!\n";
    }
}

int main() {
    custom_namespace::custom_type obj;
    
    // This works because of ADL!
    print(obj);  // No need to write custom_namespace::custom_type::print(obj)
    
    return 0;
}

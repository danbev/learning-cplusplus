#include <iostream>
#include <algorithm>  // for std::swap

namespace custom_namespace {
    struct custom_class {
        int value;
        
        custom_class(int v) : value(v) {}
    };
    
    // Custom swap function in the same namespace as custom_class
    void swap(custom_class& a, custom_class& b) {
        std::cout << "Using custom swap!\n";
        std::swap(a.value, b.value);  // swap the internals
    }
}

int main() {
    custom_namespace::custom_class obj1(10);
    custom_namespace::custom_class obj2(20);
    
    std::cout << "Before: obj1=" << obj1.value << ", obj2=" << obj2.value << "\n";
    
    // This calls our custom swap through ADL!
    {
        using std::swap;
        swap(obj1, obj2);
    }
    
    std::cout << "After: obj1=" << obj1.value << ", obj2=" << obj2.value << "\n";
    
    return 0;
}

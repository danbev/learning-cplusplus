#include <iostream>

void show_rvalue_address(int&& x) {
    std::cout << "Rvalue " << x << " is stored at address: " << &x << std::endl;
}

template<typename T> void universal_ref(T&& x) {
    std::cout << "universal_ref: x = " << x << " at " << &x << std::endl;
}

int main() {
    // What you wrote:
    show_rvalue_address(42);
    
    // What the compiler effectively generates:
    {
        int temp = 42;           // Create temporary on stack
        show_rvalue_address(static_cast<int&&>(temp));  // Pass as rvalue ref
        //show_rvalue_address(temp);  // Pass as rvalue ref
        // temp destroyed here
    }

    int x = 18;
    universal_ref(x);  // Pass lvalue
    
    // Same for the bound reference:
    int&& rref = 99;
    // Compiler generates:
    // int temp2 = 99;
    // int&& rref = static_cast<int&&>(temp2);
    // temp2's lifetime extended to match rref's scope
    
    std::cout << "Bound rvalue address: " << &rref << std::endl;
    
    return 0;
}

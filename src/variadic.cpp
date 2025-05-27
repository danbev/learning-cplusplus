#include <iostream>

void print() {
    std::cout << "(base case)" << std::endl;
}

// Variadic template function
template<typename T, typename... Args>
void print(T first, Args... rest) {
    std::cout << first << " ";
    print(rest...);  // Recursive call with remaining arguments
}

int main() {
    // Examples of using the variadic template
    print("Hello", "world!");
    print(1, 2, 3, 4, 5);
    print("Mixed:", 42, 3.14, "types");
    print("Single argument");
    
    return 0;
}

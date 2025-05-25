#include <iostream>
#include <cstring>

template<typename T>
struct print_traits {
    static void print(const T & value) {
        std::cout << "Generic: " << value << std::endl;
    }
};

template<>
struct print_traits<int> {
    static void print(const int & value) {
        std::cout << "Integer: " << value << " (hex: 0x" << std::hex << value << ")" << std::endl;
        std::cout << std::dec;
    }
};

template<>
struct print_traits<double> {
    static void print(const double & value) {
        std::cout << "Double: " << std::fixed << value << " (scientific: " << std::scientific << value << ")" << std::endl;
    }
};

template<>
struct print_traits<const char *> {
    static void print(const char * const & value) {
        std::cout << "String: \"" << value << "\" (length: " << strlen(value) << ")" << std::endl;
    }
};

template<typename T>
void smart_print(const T& value) {
    print_traits<T>::print(value);
}

int main() {
    smart_print<int>(42);
    smart_print(42);
    smart_print(3.14159);
    smart_print("Bajja");
    smart_print('B');
    
    return 0;
}

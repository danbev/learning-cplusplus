#include <iostream>

extern "C" {
    int b_lib_function();
}

extern "C" {
    int a_lib_function() {
        std::cout << "a_lib_function in a.so\n";
        return b_lib_function();
    }
}


#include <iostream>

extern "C" {
    int b_lib_function() {
        std::cout << "b_lib_function in a.so\n";
        return 18;
    }
}


#include <iostream>
#include <type_traits>
    
template<bool Condition, typename T = void>
struct my_enable_if {
};

template<typename T>
struct my_enable_if<true, T> {
    using type = T;
};

template<typename T>
typename my_enable_if<std::is_integral<T>::value, T>::type double_if(T value) {
    return value * 2;
}

template<typename T>
typename my_enable_if<std::is_floating_point<T>::value, T>::type double_if(T value) {
    return value * 3.0;
}

int main(int argc, char** argv) {
    int result = double_if(21);
    std::cout << "Result: " << result << std::endl;

    float result2 = double_if(6.3);
    std::cout << "Result2: " << result2 << std::endl;
    return 0;
}

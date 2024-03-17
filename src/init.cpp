#include <iostream>

int main() {
    int a = 1;
    std::cout << "a = " << a << std::endl;
    int b(2);
    std::cout << "b = " << b << std::endl;
    int c = (3);
    std::cout << "c = " << c << std::endl;
    int d = (1, 2, 3, 4);
    std::cout << "d = " << d << std::endl;
}

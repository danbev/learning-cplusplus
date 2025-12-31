#include <iostream>
#include <initializer_list>
#include <algorithm>

template<int N>
class Integers {
public:
    Integers(std::initializer_list<int> list) {
        std::copy(list.begin(), list.end(), data);
    }

    int* begin() {
        return &data[0];
    }

    int* end() {
        return &data[N];
    }

private:
    int data[N];
};

int main() {
    Integers<10> ints = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int x : ints) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // What the compiler does under the hood:
    {
        auto&& __range = ints;

        auto __begin = __range.begin();
        auto __end   = __range.end();

        for (; __begin != __end; ++__begin) {
            int x = *__begin;
            std::cout << "  Value: " << x << '\n';
        }
    }

    return 0;
}

#include <iostream>
#include <algorithm>
#include <initializer_list>

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

    const int* begin() const { 
        return &data[0]; 
    }

    const int* end() const { 
        return &data[N]; 
    }

    const int* cbegin() const {
        return &data[0];
    }

    const int* cend() const {
        return &data[N];
    }

private:
    int data[N];
};

void print_ints(const Integers<5> & ints) {
    std::cout << "Printing constant ints: ";
    
    // This will used the 'begin() const' version.
    for (int x : ints) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}

int main() {
    Integers<5> ints = {10, 20, 30, 40, 50};

    // This will use the non-const begin()/end()
    std::cout << "Modifying data...\n";
    for (int & x : ints) {
        x = x + 1;
    }

    // We pass the non-const ints to a const-reference function
    print_ints(ints);

    for (const int * it = ints.cbegin(); it != ints.cend(); ++it) {
        std::cout << "const value: " << *it << "\n";
    }

    return 0;
}

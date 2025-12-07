#include <cstdio>
#include <string>

class Gotcha {
private:
    std::string name;
    int age;

public:
    Gotcha() : name("Unknown"), age(0) {
        printf("Default constructor\n");
    }

    Gotcha(const std::string& n, int r) : name(n), age(r) {
        printf("Parameterized constructor\n");
    }

    Gotcha(const Gotcha& other) : name(other.name), age(other.age) {
        printf("Copy constructor\n");
    }

    Gotcha(Gotcha&& other) noexcept : name(std::move(other.name)), age(other.age) {
        printf("Move constructor\n");
    }

    // Note that this is the assignment operator (not a constructor)
    Gotcha& operator=(const Gotcha& other) {
        printf("Copy assignment operator\n");
        if (this != &other) {
            name = other.name;
            age  = other.age;
        }
        return *this;
    }

};

int main() {
    printf("Direct initialization\n");
    Gotcha a("Axe", 3);

    // So just reading this one would expect that the parameterized constructor
    // runs first to create a temporary object, and that a copy of move constructor
    // would then be called to initialize b from that temporary. But what happens
    // is that the compiler optimizes away the extra copy/move and just constructs
    // b directly from the parameters. This is called copy elision.
    printf("\nCopy elision (C++17 guaranteed)\n");
    Gotcha b = Gotcha("Sword", 2);

    printf("\nNamed object + copy\n");
    Gotcha temp1("Shield", 1); // parameterized constructor
    Gotcha c = temp1; // copy constructor


    printf("\nNamed object + move\n");
    Gotcha temp2("Bow", 4);
    Gotcha d = std::move(temp2);

    {
        printf("\nMost vexing function examples\n");
        // function declaration, no constructor called
        Gotcha x();
        auto x2();
        printf("Non constructor called for function declaration!\n");
    }

    printf("\nVarious other constructions\n");
    { Gotcha y;    }
    { Gotcha y{}; }
    { Gotcha("something", 18); }
    { Gotcha f{"something", 18}; }

    {
        printf("\nAssignment operator test\n");
        Gotcha a("test", -1);
        Gotcha b("test", -1);
        a = b;
    }

    return 0;
}


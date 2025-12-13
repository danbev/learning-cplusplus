#include <cstdio>

class bad_order {
private:
    const int result;
    const int input;

public:
    bad_order(int x) : input(x), result(input * 2) {
        printf("bad_order: result = %d\n", result);
    }
};

class good_order {
private:
    const int input; // needs to be declared before result_
    const int result;

public:
    good_order(int x) : input(x), result(input * 2) {
        printf("good_order: result = %d\n", result);
    }
};

int main() {
    bad_order bad_obj(5);
    good_order good_obj(5);
    return 0;
}

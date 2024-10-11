#include <cstdio>
#include <initializer_list>

int main(int argc, char** argv) {

    for (int x : {3, 10, 4, 20} ) {
        printf("x = %d\n", x);
    }
    return 0;
}

#include <cstdio>
#include <string>

int main(int argc, char** argv) {
    bool b = false;
    if (auto var = "something"; b) {
        printf("The variable is: %s\n", var);
    } else {
        printf("Condition is false, variable is still: %s\n", var);
    }
    return 0;
}

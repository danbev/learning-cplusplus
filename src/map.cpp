#include <map>
#include <stdexcept>
#include <stdio.h>

int main(int argc, char** argv) {
    fprintf(stdout, "map example\n");

    std::map<int, int> m;
    printf("m size: %d\n", m.size());
    m[1] = 1;

    printf("m[1] = %d\n", m[1]);
    // Notice that m[inx] will insert a new element if it doesn't exist!
    printf("m[2] = %d\n", m[2]);
    printf("m size: %d\n", m.size());

    printf("m.at(1) = %d\n", m.at(1));
    try {
        printf("m.at(3) = %d\n", m.at(3));
    } catch (std::out_of_range& e) {
        printf("m.at(3) will throw an exeption if the value does not exist!\n");
    }

    return 0;
}

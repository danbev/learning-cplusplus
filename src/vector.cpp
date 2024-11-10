#include <vector>
#include <stdio.h>

int main(int argc, char** argv) {
    fprintf(stdout, "Vector example\n");

    std::vector<int> v = {10, 20, 30, 40};
    auto it1 = v.begin() + 0;
    auto it2 = v.begin();
    printf("%d: \n", (it1 - it2));
    return 0;
}

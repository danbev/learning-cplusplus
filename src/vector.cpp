#include <vector>
#include <cstdio>

int main(int argc, char** argv) {
    fprintf(stdout, "Vector example\n");

    std::vector<int> v = {10, 20, 30, 40};
    auto it1 = v.begin() + 0;
    printf("%d\n", *it1);
    return 0;
}

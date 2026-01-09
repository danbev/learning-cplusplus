#include <vector>
#include <numeric>
#include <cstdio>

int main(int argc, char** argv) {
    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 5);

    for (int n : v) {
        printf("%d ", n);
    }

    return 0;
}


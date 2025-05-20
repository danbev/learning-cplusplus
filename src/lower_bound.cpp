#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12};

    // find the first value that is greater than or equal to given value in the vector.
    auto it = std::lower_bound(v.begin(), v.end(), 8,
        [](int value, int target) {
            return value < target;
        }
    );
    // it value is: 8, index: 7
    // Notice that this is returning the target value that is equal to the target
    // value or the first value that is greater than the target value.
    printf("it value is: %d, index: %ld\n", *it, it - v.begin());

    auto it2 = std::lower_bound(v.begin(), v.end(), 11,
        [](int value, int target) {
            return value < target;
        }
    );
    printf("it2 value is: %d, index: %ld\n", *it2, it2 - v.begin());

}

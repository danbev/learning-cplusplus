#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdio>

bool is_even(int n) {
    return n % 2 == 0;
}

int main() {
    std::vector<int> source{10, 20, 30};

    std::vector<int> destination;

    // If we used destination.begin() here, it would crash because size is 0.
    // back_inserter turns assignments into push_back calls.
    std::copy(source.begin(), source.end(), std::back_inserter(destination));

    printf("Destination contains %zu elements:\n", destination.size());
    for (auto i : destination) {
        printf("%d\n", i);
    }

    // Now lets say we want to filter a list of values. We don't know ahead of time
    // how many values we will keep, so we use back_inserter again.
    std::vector<int> values{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> evens;
    std::copy_if(values.begin(), values.end(),
                 std::back_inserter(evens),
                 is_even);

    printf("Even elements (%ld):\n", evens.size());
    for (auto e : evens) {
        printf("%d\n", e);
    }
    
    return 0;
}

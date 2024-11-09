#include <algorithm>
#include <vector>

auto isPositive(int n) -> bool { 
    return n > 0; 
}

int main(int argc, char** argv) {
    // Example 1: Check if all numbers are positive
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    bool all_positive = std::all_of(numbers.begin(), numbers.end(), 
                                  [](int n) -> int { return n > 0; });

    printf("all_positive: %d\n", all_positive);

    int arr[] = {0, 4, 6, 8, 10};
    bool all_even = std::all_of(arr, arr + 1,
                               [](int n) { 
			       printf("n: %d\n", n);
			       return n % 2 == 0; 
			       });
    printf("all_even: %d\n", all_even);

    int arr2[] = {3, 4, 6, 8, 10};
    bool all_even2 = std::all_of(arr2, arr2 + 5,
                               [](int n) { 
			       printf("n: %d\n", n);
			       return n % 2 == 0; 
			       });
    printf("all_even2: %d\n", all_even2);

    return 0;
}

#include <cstdio>
#include <vector>
#include <numeric>

int main() {
    std::vector<int> original = {3, 1, 4, 1, 5};
    // Imagine these values being the velocity at discrete time intervals.
    printf("Original sequence: ");
    for (int val : original) {
        printf("%d ", val);
    }
    printf("\n");
    
    std::vector<int> integrated(5);
    std::partial_sum(original.begin(), original.end(), integrated.begin());
    // 3  1  4  1  5
    // 3  4  8  9  14
    // integration is the total accumulation up to each point, which is exacty
    // what partial_sum does. For example, at time position 2, the total is meters
    // traveled is 3 + 1 + 4 = 8.
    printf("Integrated: ");
    for (int val : integrated) {
        printf("%d ", val);
    }
    printf("\n");
    
    std::vector<int> differentiated(5);
    std::adjacent_difference(integrated.begin(), integrated.end(), differentiated.begin());
    // So we have the total meters traveled at each point in time. To recover
    // we need to take the difference between each point which is exactly what
    // adjacent_difference does. 
    // 3     4      8     9     14    (positions)
    // 3   (4-3)  (8-4) (9-8) (14-9)
    // 3     1      4     1      5
    // So this has recovered the original sequence, the velocity at each time point.
    printf("Differentiated: ");
    for (int val : differentiated) {
        printf("%d ", val);
    }
    printf("\n");
    
    printf("Recovered original? %s\n", (original == differentiated ? "yes" : "no"));
}

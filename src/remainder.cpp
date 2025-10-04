#include <cstdio>

int main(int argc, char** argv) {
    int n = 13;
    int n_groups = 4;
    int remainder = n % n_groups;
    int n_processed = n - remainder;
    printf("Elements in complete groups: %d\n", n_processed);

    for (int i = 0; i < n_processed; i += n_groups) {
        printf("Processing group starting at index %d\n", i);
    }

    for (int i = n_processed; i < n; ++i) {
        printf("Processing remainder index %d\n", i);
    }

    return 0;
}

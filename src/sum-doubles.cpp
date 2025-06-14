#include <cstdio>
#include <chrono>

/*
 * Naive baseline for summing two arrays of doubles.
 */
int main() {
    const int N = 100000000;
    double * a = new double[N];
    for (int i = 0; i < N; ++i) {
        a[i] = i * 1.0;
    }
    printf("Initialized array a\n");

    auto start = std::chrono::high_resolution_clock::now();
    double sum = 0.0;
    for (int i = 0; i < N; ++i) {
        sum += a[i];
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto compute_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);


    printf("sum: %.0f\n", sum);
    printf("Computation time: %.2f ms (%.3f s)\n", compute_duration.count() / 1000.0, compute_duration.count() / 1000000.0);


    delete[] a;

    return 0;
}

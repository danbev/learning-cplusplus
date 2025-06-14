#include <cstdio>
#include <chrono>

/*
 * Example of unrolling a loop to sum an array of doubles.
 */
int main() {
    const int N = 100000000;
    double * a = new double[N];
    for (int i = 0; i < N; ++i) {
        a[i] = i * 1.0;
    }
    printf("Initialized array a\n");

    auto start = std::chrono::high_resolution_clock::now();
    double sum0 = 0.0;
    double sum1 = 0.0;
    double sum2 = 0.0;
    double sum3 = 0.0;
    for (int i = 0; i < N; i+=4) {
        sum0 += a[i];
        sum1 += a[i+1];
        sum2 += a[i+2];
        sum3 += a[i+3];
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto compute_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    double sum = (sum0 + sum1) + (sum2 + sum3);

    printf("sum: %.0f\n", sum);
    printf("Computation time: %.2f ms (%.3f s)\n", compute_duration.count() / 1000.0, compute_duration.count() / 1000000.0);


    delete[] a;

    return 0;
}

#include <cstdio>
#include <chrono>
#include <immintrin.h>  // For AVX2 intrinsics

/*
 * Example using AVX2 intrinsics to sum an array of doubles.
 * AVX2 can process 4 doubles (256 bits) in a single instruction.
 */
int main() {
    const int N = 100000000;
    
    // Align memory to 32-byte boundary for optimal AVX2 performance
    double * a = (double*) aligned_alloc(32, N * sizeof(double));
    
    for (int i = 0; i < N; ++i) {
        a[i] = i * 1.0;
    }
    printf("Initialized array a (N = %d)\n", N);

    auto start = std::chrono::high_resolution_clock::now();
    
    // AVX2 sum using 256-bit vectors (4 doubles each)
    __m256d sum_vec = _mm256_setzero_pd();  // Initialize to [0.0, 0.0, 0.0, 0.0]
    
    int simd_end = N - (N % 4);  // Process in chunks of 4
    
    for (int i = 0; i < simd_end; i += 4) {
        // Load 4 doubles from memory into 256-bit register
        __m256d data_vec = _mm256_load_pd(&a[i]);  // loadu = unaligned load
        
        // Add to running sum: sum_vec += data_vec
        sum_vec = _mm256_add_pd(sum_vec, data_vec);
    }
    
    // Extract the 4 doubles from the vector and sum them
    double sum_array[4];
    _mm256_storeu_pd(sum_array, sum_vec);
    double sum = sum_array[0] + sum_array[1] + sum_array[2] + sum_array[3];
    
    // Handle residual elements (scalar code)
    for (int i = simd_end; i < N; ++i) {
        sum += a[i];
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto compute_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    printf("SIMD sum components: %.0f, %.0f, %.0f, %.0f\n", sum_array[0], sum_array[1], sum_array[2], sum_array[3]);
    printf("Total sum: %.0f\n", sum);
    printf("Computation time: %.2f ms (%.3f s)\n", compute_duration.count() / 1000.0, compute_duration.count() / 1000000.0);

    free(a);  // Use free() with aligned_alloc()
    return 0;
}

cmake_minimum_required(VERSION 3.10)
project(CheckSourceRunsDemo C)

# Include the CheckCSourceRuns module
include(CheckCSourceRuns)

# Test for math.h and sin function
set(MATH_TEST_CODE "
#include <math.h>
int main() {
    double result = sin(0.5);
    return (result > 0.0 && result < 1.0) ? 0 : 1;
}
")

# Test for SSE4.1 support with compiler flags
set(CMAKE_REQUIRED_FLAGS "-msse4.1")
set(SSE41_TEST_CODE "
#include <smmintrin.h>
int main() {
    __m128i a = _mm_set1_epi32(1);
    __m128i b = _mm_set1_epi32(2);
    __m128i c = _mm_add_epi32(a, b);
    int result = _mm_extract_epi32(c, 0);
    return result == 3 ? 0 : 1;
}
")

# Test for AVX support with compiler flags
set(CMAKE_REQUIRED_FLAGS "-mavx")
set(AVX_TEST_CODE "
#include <immintrin.h>
int main() {
    __m256 a = _mm256_set1_ps(1.0f);
    __m256 b = _mm256_set1_ps(2.0f);
    __m256 c = _mm256_add_ps(a, b);
    // Store the result to memory instead of using extract
    float result[8];
    _mm256_storeu_ps(result, c);
    return (result[0] == 3.0f) ? 0 : 1;
}
")

# Run the tests (reset flags between tests)
check_c_source_runs("${MATH_TEST_CODE}" HAS_MATH)

set(CMAKE_REQUIRED_FLAGS "-msse4.1")
check_c_source_runs("${SSE41_TEST_CODE}" HAS_SSE41)

set(CMAKE_REQUIRED_FLAGS "-mavx")
check_c_source_runs("${AVX_TEST_CODE}" HAS_AVX)

# Debug info
message(STATUS "AVX test result: ${HAS_AVX}")

# Reset required flags
set(CMAKE_REQUIRED_FLAGS "")

# Reset required flags
set(CMAKE_REQUIRED_FLAGS "")

# Print the results
message(STATUS "Math library available: ${HAS_MATH}")
message(STATUS "SSE4.1 support: ${HAS_SSE41}")
message(STATUS "AVX support: ${HAS_AVX}")

# Set up arch flags and definitions based on detected capabilities
set(GGML_CPU_NAME "ggml-cpu")
set(ARCH_FLAGS "")
set(ARCH_DEFINITIONS "")

if(HAS_AVX)
  set(ARCH_FLAGS "${ARCH_FLAGS} -mavx")
  set(ARCH_DEFINITIONS "${ARCH_DEFINITIONS}GGML_AVX;")
else()
  # Fallback to basic architecture
  set(ARCH_FLAGS "${ARCH_FLAGS} -msse2")
  set(ARCH_DEFINITIONS "${ARCH_DEFINITIONS}GGML_SSE2;")
endif()

if(HAS_SSE41)
  set(ARCH_FLAGS "${ARCH_FLAGS} -msse4.1")
  set(ARCH_DEFINITIONS "${ARCH_DEFINITIONS}GGML_SSE41;")
endif()

# Always show the message regardless of test results
message(STATUS "Adding CPU backend variant ${GGML_CPU_NAME}: ${ARCH_FLAGS} ${ARCH_DEFINITIONS}")

# Create a simple executable to demonstrate we're done
add_executable(demo main.c)

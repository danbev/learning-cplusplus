#include <span>
#include <cstdio>

void process(float * samples, int n_samples) {
    printf("processing using pointer and size...\n");
    for (int i = 0; i < n_samples; ++i) {
        printf("%f, ", samples[i]);
    }
    printf("\n");
}

void process_span(std::span<const float> samples) {
    printf("processing using span...\n");
    for (int i = 0; i < samples.size(); ++i) {
        printf("%f, ", samples[i]);
    }
    printf("\n");
}

int main(int args, char** argv) {
    constexpr int size = 4;
    float samples[size] = {1, 2, 3, 4};
    process(samples, size);
    process_span(samples);
    process_span(std::span(samples, size));
    return 0;
}

#include <cstdio>
#include <cstdint>
#include <string>
#include <chrono>

std::string timestamp_to_string(uint64_t timestamp_ms) {
    uint64_t hours = timestamp_ms / (1000 * 60 * 60);
    uint64_t minutes = (timestamp_ms % (1000 * 60 * 60)) / (1000 * 60);
    uint64_t seconds = (timestamp_ms % (1000 * 60)) / 1000;
    uint64_t milliseconds = timestamp_ms % 1000;

    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%02lu:%02lu:%02lu.%03lu", hours, minutes, seconds, milliseconds);
    return std::string(buffer);
}

inline int64_t seconds_to_centiseconds(double seconds) {
    return static_cast<int64_t>(seconds * 100.0 + 0.5);
}

inline double centiseconds_to_seconds(uint64_t centiseconds) {
    return static_cast<double>(centiseconds) / 100.0;
}

int main() {
    int64_t timestamp = 2000; // 2000 ms (2 seconds)
    printf("timestamp: %s\n", timestamp_to_string(timestamp).c_str());

    int64_t ten_ms = 10;
    printf("ten_ms: %s\n", timestamp_to_string(ten_ms).c_str());

    printf("Rounding example and why it is important:\n");
    double d = 1.946;
    printf("d: %d\n", (int)( d * 100.0));
    printf("d: %d\n", (int)( d * 100.0 + 0.5));

    return 0;
}

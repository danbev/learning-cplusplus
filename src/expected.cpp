#include <expected>
#include <string>
#include <cstdio>

std::expected<int, std::string> divide(int a, int b) {
    if (b == 0) {
        return std::unexpected("divide by 0 error");
    }
    return a / b;
}

int main(int argc, char ** argv) {
    printf("std::expected example...\n");
    auto result = divide(10, 0);

    if (result) {
        printf("result: %d\n", *result);
    } else {
        printf("error: %s\n", result.error().c_str());
    }

    printf("result: %d\n", result.value_or(-1));

    return 0;
}

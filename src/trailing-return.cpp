#include <cstdio>

void handler(float f) {
    printf("Handler received float: %.2f\n", f);
}

void (*process(int mode))(float) {
    printf("Process called with mode: %d\n", mode);
    return &handler;
}

auto modern(int mode) -> void (*)(float) {
    printf("Modern called with mode: %d\n", mode);
    return &handler;
}

int main(int argc, char** argv) {
    void (*ptr)(float) = process(5);
    ptr(3.14f);

    auto modernPtr = modern(10);
    modernPtr(2.71f);
    return 0;
}

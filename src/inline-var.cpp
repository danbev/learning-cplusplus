#include "inline-var.h"
#include <cstdio>

int main() {
    printf("inline variable example...\n");
    printf("something::var = %d\n", something::var);
    return 0;
}

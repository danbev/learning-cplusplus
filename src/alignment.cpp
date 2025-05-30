#include <cstdio>

struct non_aligned {
    bool a;  // 1 byte.
    int  b;  // 4 bytes (aligned to 4-byte boundary).
    bool c;  // 1 byte (but needs end padding to be aligned to the alignement requirement.
    // Total: 1 + 3 (padding) + 4 + 1 + 3 (padding) = 12 bytes
};

struct better_aligned {
    int  b;  // 4 bytes
    bool a;  // 1 byte, 
    bool c;  // 1 byte (but needs end padding to be aligned to the alignement requirement.
    // Total: 4 + 1 + 1 + 2 (padding) = 8 bytes (33% smaller than non_aligned)
};

struct __attribute__((packed)) packed_struct {
    int  b;  // 4 bytes
    bool a;  // 1 byte  
    bool c;  // 1 byte
    // Total: 4 + 1 + 1  = 6 bytes, no padding
}; 

struct cache_friendly {
    int32_t data[8];  // 32 bytes - fits nicely in cache line
};

struct cache_unfriendly {
    int32_t data[20]; // 80 bytes - spans multiple cache lines
};

int main() {
    printf("Size of non_aligned   : %zu\n", sizeof(non_aligned));
    printf("Size of better_aligned: %zu\n", sizeof(better_aligned));
    printf("Size of packed_struct : %zu\n", sizeof(packed_struct));
    printf("Size of cache_friendly: %zu\n", sizeof(cache_friendly));
    printf("Size of cache_unfriendly: %zu\n", sizeof(cache_unfriendly));

    return 0;
}

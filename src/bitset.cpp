#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define BITSET_SHR 5

// sizeof(uint32_t) = 4, 4*8 = 32, 32 - 1 = 31
#define BITSET_MASK (sizeof(uint32_t) * 8 - 1)

// This function is used to calculate the number of elements that are needed
// in for the used array in the hash_set struct.
//
// n is the number of bits we want to be able to store.
//
// If n = 10, 10 + 31 >> 5 = 41 >> 5 = 1
// If n = 32, 32 + 31 >> 5 = 63 >> 5 = 1
// If n = 33, 33 + 31 >> 5 = 64 >> 5 = 2
static size_t bitset_size(size_t n) {
    // BITSET_MASK = 31
    return (n + BITSET_MASK) >> 5;
}

//
// index >> BITSET_SHR = index / 32 which gives us the index of the uint32_t
// where the value for the index is stored.
static inline bool bitset_get(const uint32_t* bitset, size_t i) {
    return !!(bitset[i >> BITSET_SHR] & (1u << (i & BITSET_MASK)));
}

static inline void bitset_set(uint32_t* bitset, size_t i) {
    bitset[i >> BITSET_SHR] |= (1u << (i & BITSET_MASK));
}

static inline void bitset_clear(uint32_t* bitset, size_t i) {
    bitset[i >> BITSET_SHR] &= ~(1u << (i & BITSET_MASK));
}

struct things {
    int x;
};
                                                                                   
struct hash_set {
    size_t size;
    uint32_t* used;
    struct things** keys;
};

int main(int argc, char** argv) {
    int size = 3;
    hash_set set;
    set.keys = (struct things**) malloc(sizeof(struct things*) * size);
    set.used = (uint32_t*) malloc(sizeof(uint32_t) * bitset_size(size));

    bool b = bitset_get(set.used, 0);
    printf("b = %d\n", b);
    bitset_set(set.used, 0);
    b = bitset_get(set.used, 0);
    printf("b = %d\n", b);

    return 0;
}

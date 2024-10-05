#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define BITSET_SHR 5
#define HASHSET_ALREADY_EXISTS ((size_t)-2)

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

// We find the index of the uint32_t where the value for the index is stored using:
// index >> BITSET_SHR = index / 32 which gives us the index of the uint32_t where
// the value for the index is stored.
// Then we find the bit position of the value using:
// 1u << (index & BITSET_MASK)
// We then AND the two values to get the value of the bit at the index. This value is
// zero if the bit is not set but can be a value greater than zero if the bit is set.
// In our case we only want to return a bool, true if the bit that is the AND operation
// was not zero, and false if the bit was zero. We can do this by using the double negation
// operator (!!) which will return true if the value is not zero and false if the value is zero.
static inline bool bitset_isset(const uint32_t* bitset, size_t i) {
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

static inline size_t hash(const struct things * ptr) {
    return (size_t)(uintptr_t) ptr;
}

// Notice that we are here casting -1 to a size_t. Now, size_t is an unsigned integer
// so it cannot represent negative numbers. When we cast -1 to a size_t we get the
// largest possible value that can be represented by a size_t.
#define HASHSET_FULL ((size_t)-1)

static size_t hash_find_idx(const struct hash_set* hash_set, struct things* key) {
    // Get the hash value and then "compress" it into the range of the hash_set.
    size_t h = hash(key) % hash_set->size;

    // linear probing
    size_t i = h;
    // While the the index i is set, and the key at the index i is not the key we are
    // looking for we increment the index i by one.
    while (bitset_isset(hash_set->used, i) && hash_set->keys[i] != key) {
	// We increment the slot by one and need to make sure that if we reach the end
	// of the range we wrap around to the beginning of the range.
        i = (i + 1) % hash_set->size;
	// If i is the same value that we started off with then we have checked all
	// slots.
        if (i == h) {
            return HASHSET_FULL;
        }
    }
    return i;
}

static bool hash_contains(const struct hash_set* hash_set, struct things* key) {
    size_t idx = hash_find_idx(hash_set, key);
    return idx != HASHSET_FULL && bitset_isset(hash_set->used, idx);
}

static size_t hash_insert(struct hash_set* hash_set, struct things* key) {
    size_t h = hash(key) % hash_set->size;

    // linear probing
    size_t i = h;
    do {
	// If the slot is not set then we set the slot as used and set the
	// key at that index to the key.
        if (!bitset_isset(hash_set->used, i)) {
            bitset_set(hash_set->used, i);
            hash_set->keys[i] = key;
            return i;
        }

        if (hash_set->keys[i] == key) {
            return HASHSET_ALREADY_EXISTS;
        }
	// We increment the slot by one and need to make sure that if we reach the end
	// of the range we wrap around to the beginning of the range. Same as we did in
	// the hash_find_idx function.
        i = (i + 1) % hash_set->size;
    } while (i != h);

    // visited all hash table entries -> not found
    printf("fatal error\n");
    abort();
}

int main(int argc, char** argv) {
    int size = 3;
    hash_set set;
    set.size = size;
    set.keys = (struct things**) malloc(sizeof(struct things*) * size);
    set.used = (uint32_t*) malloc(sizeof(uint32_t) * bitset_size(size));

    bool b = bitset_isset(set.used, 0);
    printf("b = %d\n", b);
    bitset_set(set.used, 0);
    b = bitset_isset(set.used, 0);
    printf("b = %d\n", b);
    struct things t = {0};
    printf("hash = %zu\n", hash(&t));

    size_t idx = hash_find_idx(&set, &t);
    printf("idx = %zu\n", idx);

    bool contains = hash_contains(&set, &t);
    printf("contains = %s\n", contains ? "true" : "false");

    size_t inserted_idx = hash_insert(&set, &t);
    printf("inserted_idx = %zu\n", inserted_idx);
    contains = hash_contains(&set, &t);
    printf("contains = %s\n", contains ? "true" : "false");
    return 0;
}

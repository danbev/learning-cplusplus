#include <cstdio>
#include <vector>

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

struct struct_with_vector {
    std::vector<int> vec;
    // int * data_ptr 8 bytes (on 64-bit systems)
    // size_t size 8 bytes (current number of elements)
    // size_t capacity 8 bytes (total allocated space)
    // The largest member is 8 in this case which is the alignment requirement.
};

void print_type_alignments() {
    printf("=== TYPE ALIGNMENT REQUIREMENTS ===\n\n");

    printf("Type alignments on this system:\n");
    printf("char:      %zu byte alignment\n", alignof(char));
    printf("short:     %zu byte alignment\n", alignof(short));
    printf("int:       %zu byte alignment\n", alignof(int));
    printf("long:      %zu byte alignment\n", alignof(long));
    printf("long long: %zu byte alignment\n", alignof(long long));
    printf("float:     %zu byte alignment\n", alignof(float));
    printf("double:    %zu byte alignment\n", alignof(double));
    printf("pointer:   %zu byte alignment\n", alignof(void*));
    printf("\n");

    printf("What this means:\n");
    printf("- char can start at ANY address                 (0, 1, 2, 3, 4, 5, ...)\n");
    printf("- short must start at EVEN addresses            (0, 2, 4, 6, 8, ...)\n");
    printf("- int must start at addresses divisible by 4    (0, 4, 8, 12, ...)\n");
    printf("- double must start at addresses divisible by 8 (0, 8, 16, 24, ...)\n");
    printf("\n");
}

int main() {
    printf("Size of non_aligned   : %zu, alignof: %zu\n", sizeof(non_aligned), alignof(non_aligned));
    printf("Size of better_aligned: %zu, alignof: %zu\n", sizeof(better_aligned), alignof(better_aligned));
    printf("Size of packed_struct : %zu, alignof: %zu\n", sizeof(packed_struct), alignof(packed_struct));
    printf("Size of cache_friendly: %zu, alignof: %zu\n", sizeof(cache_friendly), alignof(cache_friendly));
    printf("Size of cache_unfriendly: %zu, alignof: %zu\n", sizeof(cache_unfriendly), alignof(cache_unfriendly));
    printf("Size of struct_with_vector: %zu, alignof: %zu\n", sizeof(struct_with_vector), alignof(struct_with_vector));

    print_type_alignments();
    return 0;
}

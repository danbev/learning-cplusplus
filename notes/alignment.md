## Alignment notes

### Alignment requirement
When defining a struct, it is often beneficial to place larger member types first. This can
help reduce padding and improve memory alignment, leading to more efficient memory
usage and potentially better performance.

For example, if 
```c++
struct non_aligned {
    bool a;
    int  b;
    bool c;
    // Total: 1 + 3 (padding) + 4 + 1 + 3 (padding) = 12 bytes
};
```
The issue here is that `b` which is an int, 4 bytes, needs to start/be aligned on a 
4 byte boundry, but `a` is only 1 byte, so there needs to be an additional 3 bytes of
padding for the start of `b`.

Now `c`, only needs 1 byte but there will also be end padding after it to make sure
that the struct itself is aligned to the largest member's alignment requirement, which is 4 bytes.
Why would this be needed? Like if "we" placed a struct of this type on the stack it would take
up 12 bytes. And placing another struct directly afterwards would still make the bool member
aligned. When the CPU reads memory it does so in aligned chunks (like 4, 8 or 16 bytes), and if
the data is not aligned on those boundries, it can lead to performance penalties like requiring
multiple memory accesses.

Type-Specific Requirements

* char:   1-byte alignment (can start anywhere)
* short:  2-byte alignment (must start at even addresses)
* int:    4-byte alignment (must start at addresses divisible by 4)
* double: 8-byte alignment (must start at addresses divisible by 8)

But if we place `b` first then it is aligned and we can place `a` and `c` directly
after `b`:
```c++
struct better_aligned {
    int  b;  // 4 bytes
    bool a;  // 1 byte, 
    bool c;  // 1 byte (but needs end padding to be aligned to the alignement requirement.
    // Total: 4 + 1 + 1 + 2 (padding) = 8 bytes (33% smaller than non_aligned)
};
```

### packed
We can tell the compiler to ignore the alignment requirement for member of a struct
in which case the alignment requirement will be 1. And no padding will be added.
This means that this struct can start at any address.
```c++
struct __attribute__((packed)) packed_struct {
    int  b;  // 4 bytes
    bool a;  // 1 byte  
    bool c;  // 1 byte
    // Total: 4 + 1 + 1  = 6 bytes, no padding
}; 
```
Note that using this might lead to performance penalties, as the CPU might not be
able to read, or even crashes on platforms like ARM.

#include <cstdio>
#include <cstring>

static int round_nearsest(float fval) {
    // This adding of a "magic" number technique/trick. The goal is to cast
    // a float to an int and normally we might reach for something like:
    // int i = (int)(fval);
    // And we might think that this is just a cheap reinterpretation of the bits.
    // But this is not the case for floating point numbers, because the conversion
    // and often involves the compiler calling _ftol or similar functions which
    // can be slow.
    // The default rounding mode in the FPU is round to nearest, but the c
    // standard is round towards zero. So there is additional work that has to
    // be done in the FPU to switch rounding modes (and back again).
    //
    // The magic number 12582912.f is 2²³ + 2²², and when we add this to our
    // float value it will cause the float to be rounded to the nearest integer
    // but it is a different value than the original. But the nice thing is that
    // the representation of this float in memory is something like this:
    // Sign    : 0
    // Exponent: 150 (represents 2²³)
    // Mantissa: 500002861... (this includes the 2²²)
    float val = fval + 12582912.f;

    // Get the bit representation of the float
    int i;
    memcpy(&i, &val, sizeof(int));

    // Extract the mantissa and then subtract the offset (2²²) and we are left
    // with the rounded integer value.
    return (i & 0x007fffff) - 0x00400000;
}

int main() {
    float f = 12.34;
    int i = round_nearsest(f);
    
    printf("Rounded value of %.2f is %d\n", f, i);

    return 0;
}

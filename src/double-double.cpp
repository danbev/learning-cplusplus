#include <stdio.h>

int main() {
    printf("Double-Double Precision Example\n");

    double a = 1.0;
    double b = 1e-16;

    printf("a = %.17g, b = %.17g\n", a, b);
    // Calculate the rounded sum of a and b
    double sum = a + b;

    // Normal addition will lose precision here
    printf("Normal addition: a + b = %.17g\n", sum);

    // To preserve precision, we can use a double-double representation
    // First we figure out what the computer things b should be, based on the
    // rounded sum.
    double computed_b = sum - a;
    printf("computed_b = %.17g\n", computed_b);

    // The error formula has two parts:
    // 1) How much of the error came from the representation of a in the sum
    // 2) How much of the error came from the representation of b in the sum
    //             [ error from a ]    [error from b ]
    // sum - computed_b reconstructs the value of a from the sum.
    // a - (sum - computed_b) finds the difference between the original a and what a became.
    // b - computed_b finds the difference between the original b and the reconstructed b.
    // Adding these gives us the total rounding error that was lost.
    double error = (a - (sum - computed_b))   +    (b - computed_b);
    printf("error = %.17g\n", error);

    // So if we store the sum and the error we have the full precision?
    printf("Double-Double Representation:\n");
    printf("sum = %.17g, error = %.17g\n", sum, error);

    return 0;
}

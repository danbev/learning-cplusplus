#include <iostream>
#include <cmath>

// Our function to optimize: f(x) = x^2
double f(double x) {
    return x * x;
}

// First derivative of f(x): f'(x) = 2x
// This tells use the slope of the tangent line at any point x.
// A positive return value means the function is increasing at x.
// A negative return value means the function is decreasing at x.
// A return value of 0 means the function is at a minimum or maximum.
double f_prime(double x) {
    return 2 * x;
}

// Second derivative of f(x): f''(x) = 2
// This tells us the curvature of the function at any point x.
//
// A positive return value means the function is upward (convex) up at x.
// A negative return value means the function is downward (concave) down at x.
// A return value of 0 means the function is inflection point.
double f_double_prime(double x) {
    return 2;
}

// Perform one step of Newton's method
double newton_step(double x) {
    // The ration tells us how far to move based on the slope and curvature.
    // And we move in the opposite direction of the slope
    return x - (f_prime(x) / f_double_prime(x));
}

int main() {
    double x = 10.0;  // Starting point
    const int MAX_ITERATIONS = 30;
    const double TOLERANCE = 1e-6;

    std::cout << "Starting optimization at x = " << x << "\n";

    for (int i = 0; i < MAX_ITERATIONS; ++i) {
        double new_x = newton_step(x);
        
        std::cout << "Iteration " << i+1 << ": x = " << new_x << "\n";
        
        if (std::abs(new_x - x) < TOLERANCE) {
            std::cout << "Converged!\n";
            break;
        }
        
        x = new_x;
    }

    std::cout << "Final minimum found at x = " << x << "\n";
    std::cout << "Function value at minimum: " << f(x) << "\n";

    return 0;
}

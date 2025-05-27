#include <iostream>
#include <vector>
#include <random>

int main() {
    // Define a random number generator
    std::default_random_engine generator;

    // Define the weights for the distribution
    std::vector<double> weights = {-10, 20, 30}; // Relative probabilities

    // Create a discrete distribution with the specified weights
    std::discrete_distribution<int> distribution(weights.begin(), weights.end());

    // Generate random numbers
    for (int i = 0; i < 10; ++i) {
        int number = distribution(generator);
        std::cout << number << '\n';
    }

    return 0;
}


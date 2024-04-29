#include <iostream>
#include <random>
#include <vector>

int main() {
    std::mt19937 gen; // Uses a default seed

    // Create a discrete distribution with 3 possible outcomes
    // The numbers 0, 1, 2 are generated with different probabilities
    // The contstuctor accepts an initiliazer list so these integers are
    // convert to doubles and normalized to probabilities.
    std::discrete_distribution<> dist({2, 1, 3});

    // We can also use a vector of doubles to specify the weights.
    std::vector<double> weights = {2, 1, 3};
    std::discrete_distribution<> dist2(weights.begin(), weights.end());

    // Map to count the number of times each number is generated
    std::vector<int> outcomes(3, 0);

    // Generate a number 1000 times
    for (int n = 0; n < 1000; ++n) {
        int number = dist2(gen);
        outcomes[number]++;
    }

    // Output the counts
    for (int i = 0; i < outcomes.size(); ++i) {
        std::cout << i << " generated " << outcomes[i] << " times\n";
    }

    return 0;
}


#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 3, 5, 7, 9, 11, 13};
    for (int i = 0; i < numbers.size(); i++) {
		std::cout << "numbers[" << i << "] = " << numbers[i] << std::endl;
    }
    int target = 6;

    std::cout << "Finding the first number greater than " << target << std::endl;
    auto it = std::upper_bound(numbers.begin(), numbers.end(), target);

    if (it != numbers.end()) {
        std::cout << "First number greater than " << target 
                  << " is " << *it 
                  << " at position " << (it - numbers.begin()) << std::endl;
    } else {
        std::cout << "No number greater than " << target << " found." << std::endl;
    }

    return 0;
}

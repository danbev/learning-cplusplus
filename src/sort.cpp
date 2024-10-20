#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

template<typename T>
void print_vector(const std::vector<T>& vec) {
    for (const auto& item : vec) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    std::cout << "Original vector: ";
    print_vector(numbers);

    std::sort(numbers.begin(), numbers.end());
    std::cout << "Sorted ascending: ";
    print_vector(numbers);

    // Sort in descending order
    std::sort(numbers.begin(), numbers.end(), std::greater<int>());
    std::cout << "Sorted descending: ";
    print_vector(numbers);

    std::vector<std::string> words = {"apple", "banana", "cherry", "date", "elderberry"};
    std::cout << "\nOriginal words: ";
    print_vector(words);

    std::sort(words.begin(), words.end(), 
              [](const std::string& a, const std::string& b) {
                  return a.length() < b.length();
              });
    
    std::cout << "Sorted by length: ";
    print_vector(words);

    return 0;
}

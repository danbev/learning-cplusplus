#include <iostream>
#include <future>
#include <thread>

// Function to perform a time-consuming task (e.g., calculating the sum of numbers from 1 to N)
long long sumUpTo(int N) {
    std::cout << "Async sumUpTo running on thread: " << std::this_thread::get_id() << std::endl;
    long long sum = 0;
    for (int i = 1; i <= N; ++i) {
        sum += i;
    }
    return sum;
}

int main() {
    // Start the asynchronous task to calculate the sum of numbers up to 1000000
    std::future<long long> futureSum = std::async(std::launch::async, sumUpTo, 1000000);

    // Do other things here while the asynchronous task is running
    // For example, we just print a message
    std::cout << "Calculating..." << std::endl;

    // Wait for the asynchronous task to finish and get the result
    long long result = futureSum.get();

    // Print the result
    std::cout << "The sum is: " << result << std::endl;

    return 0;
}


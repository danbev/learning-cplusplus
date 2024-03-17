#include <shared_mutex>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::shared_mutex resourceMutex;
std::mutex coutMutex;
int sharedResource = 0;

void readerFunction(int readerId) {
    std::shared_lock<std::shared_mutex> lock(resourceMutex);
    // Multiple readers can enter this section simultaneously.
    std::lock_guard<std::mutex> coutLock(coutMutex);
    std::cout << "Reader " << readerId << " sees value " << sharedResource << std::endl;
}

void writerFunction(int newValue) {
    std::unique_lock<std::shared_mutex> lock(resourceMutex);
    sharedResource = newValue;
    // We are using a unique lock, so no other thread can enter this section
    // so we don't need to lock coutMutex.
    std::cout << "Writer updates value to " << sharedResource << std::endl;
}

int main() {
    std::vector<std::thread> readers;
    for (int i = 0; i < 5; ++i) {
        readers.push_back(std::thread(readerFunction, i));
    }

    std::thread writer(writerFunction, 10);

    for (auto& reader : readers) {
        reader.join();
    }
    writer.join();

    return 0;
}

#include <memory>

int main() {
    std::unique_ptr<int> int_ptr = std::make_unique<int>(18);
    return 0;
}

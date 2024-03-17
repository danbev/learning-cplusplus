#include <iostream>
#include <optional>

std::optional<std::string> create(bool b) {
    if (b) {
        return "Something";
    } else {
        return {};
    }
}

int main() {
    bool a = create(false).has_value();
    std::cout << "a = " << a << std::endl;

    std::string b = create(true).value();
    std::cout << "b = " << b << std::endl;

    if (auto str = create(true); str.has_value()) {
    //if (auto str = create(true)) {
        std::cout << "str = " << str.value() << std::endl;
    }

    // Default constructor and using value_or:
    std::optional<std::string> str;
    std::cout << "str = " << str.value_or("Empty") << std::endl;
    str.emplace("Emplaced");
    std::cout << "str = " << str.value() << std::endl;
}

#include <cstdio>
#include <variant>
#include <string>
#include <iostream>

int main(int argc, char** argv) {
    printf("std::variant example\n");
    std::variant<int, float, std::string> v;

    v = 10;
    int i = std::get<int>(v);
    printf("Integer value: %d\n", i);

    try {
        float f = std::get<float>(v);
    } catch (const std::bad_variant_access& e) {
        printf("Caught exception: %s\n", e.what());
    }

    v = 3.14f;
    float f = std::get<float>(v);
    printf("Float value: %f\n", f);
                                  
    v = "Hello World";
    std::string s = std::get<std::string>(v);
    printf("String value: %s\n", s.c_str());

    if (auto pval = std::get_if<int>(&v)) {
        printf("It's an int: %d ", *pval);
    } else {
        printf("It's not an int.\n");
    }

    auto print_visitor = [](const auto& val) {
        std::cout << "Value: " << val << '\n';
    };
    std::visit(print_visitor, v);

    return 0;
}

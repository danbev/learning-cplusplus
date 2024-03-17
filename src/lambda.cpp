#include <iostream>

struct Something {
  int value {123};

  auto get_value_copy() {
    return [*this] { return value; };
  }

  auto get_value_ref() {
    return [this] { return value; };
  }
};

int main() {
    Something s;
    auto value_copy = s.get_value_copy();
    auto value_ref = s.get_value_ref();
    s.value = 321;
    int v1 = value_copy(); // 123
    int v2 = value_ref(); // 321
    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;

    auto lambda = [] { return 18; };
    std::cout << "lambda() = " << lambda() << std::endl;
}

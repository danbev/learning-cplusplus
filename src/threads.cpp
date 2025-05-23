#include <cstdio>
#include <iostream>
#include <thread>
#include <string>

void hello(int x) {
    std::cout << "hello thread id: " << std::this_thread::get_id();
    printf(", x=%d\n", x);
}

void hello2(std::string const& name) {
    printf("Hello %s\n", name.c_str());
}

void ref_func(int& x) {
    x++;
    printf("ref_func %d\n", x);
}

int main() {
    int x = 10;
    std::thread t1(hello, 10);
    std::thread t2(hello2, "Fletch");
    std::thread t3(ref_func, std::ref(x));

    t1.join();
    t2.join();
    t3.join();

    return 0;
}

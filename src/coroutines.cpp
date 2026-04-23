#include <iostream>
#include <coroutine>

struct simple_handle {

    struct promise_type {

        simple_handle get_return_object() {
            return {std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        //std::suspend_always initial_suspend() {
        std::suspend_never initial_suspend() {
            return {};
        }

        std::suspend_always final_suspend() noexcept {
            return {};
        }

        void unhandled_exception() {}
        void return_void() {}
    };

    std::coroutine_handle<promise_type> handle;
};

simple_handle simple_coroutine() {
    std::string local_str = "something";

    std::cout << "  [Coroutine] Phase 1: I am running...\n";

    co_await std::suspend_always{};

    std::cout << "  [Coroutine] Phase 2: I have resumed and now I'm finishing!\n";
    std::cout << "  [Coroutine] local_str: " << local_str << '\n';
}

int main() {
    std::cout << "[Main] Calling coroutine...\n";
    simple_handle c = simple_coroutine();

    std::cout << "[Main] Resuming to start Phase 1...\n";
    c.handle.resume();

    std::cout << "[Main] The function is now suspended at the co_await. I can do other stuff.\n";

    std::cout << "[Main] Resuming to start Phase 2...\n";
    //c.handle.resume(); // needed depending on what initial_suspend returns.

    std::cout << "[Main] All done.\n";
    c.handle.destroy();
    return 0;
}

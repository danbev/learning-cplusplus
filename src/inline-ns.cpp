#include <cstdio>

namespace outer {
    inline namespace inner {
        void func() {
            printf("Hello from inner namespace!\n");
        }
    }

}

int main() {
    // Calls the function from the inner namespace but accessed
    // through the outer namespace.
    outer::func(); 
    outer::inner::func(); 

    return 0;
}

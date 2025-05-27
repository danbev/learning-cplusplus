#include <cstdio>

struct EmptyBase {
    // the base class can still have function/methods but no members.
    void print() const {
        printf("EmptyBase::print called\n");
    }
};

struct Something {
    EmptyBase eb; // size 1 + 3 bytes padding as x must be 4 byte aligned.
    int x;        // size 4.
};

struct Ebo : EmptyBase {
    int x;        // size 4.
};

int main() {
    printf("sizeof EmptyBase: %zu\n", sizeof(EmptyBase));
    printf("sizeof Something: %zu\n", sizeof(Something));
    printf("sizeof Ebo:       %zu\n", sizeof(Ebo));

    EmptyBase eb;
    EmptyBase* e = &eb;
    printf("address of EmptyBase eb: %p\n", (void*)&eb);
    printf("address of Ebo e:        %p\n", (void*)e);

    eb.print();
    e->print();

    return 0;
}

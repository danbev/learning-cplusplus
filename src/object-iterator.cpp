#include <cstdio>
#include <vector>

struct Tracer {
    int id;

    Tracer(int id_) : id(id_) {
        printf("Tracer(%d) constructed\n", id);
    }

    Tracer(const Tracer& other) : id(other.id) {
        printf("Tracer(%d) copy-constructed\n", id);
    }

    ~Tracer() {
        printf("Tracer(%d) destroyed\n", id);
    }
};

int main() {
    printf("Object iteration example (object construction)\n");

    printf("Creating vector of Tracer objects\n");
    std::vector<Tracer> v;
    v.reserve(3);  // Without this we will see copy-constructed objects as the
                   // vector resizes between emplace_back calls
    v.emplace_back(1);
    v.emplace_back(2);
    v.emplace_back(3);

    printf("\n");

    printf("range-for by VALUE (copy constructs each element)\n");
    // So each element in the vector is copy-constructed into t and
    // then destroyed at the end of the loop iteration.
    for (Tracer t : v) {
        printf("  in loop, t.id = %d\n", t.id);
    }

    printf("\n");

    printf("range-for by const ref (no copies)\n");
    for (const Tracer& t : v) {
        printf("  in loop, t.id = %d\n", t.id);
    }

    printf("range-for by ref (no copies) but can be modified\n");
    for (Tracer& t : v) {
        printf("  in loop, t.id = %d\n", t.id);
    }

    printf("range-for by const auto ref (no copies)\n");
    for (const auto & t : v) {
        printf("  in loop, t.id = %d\n", t.id);
    }

    printf("range-for by auto ref (no copies) but can be modified\n");
    for (auto& t : v) {
        printf("  in loop, t.id = %d\n", t.id);
    }

    return 0;
}


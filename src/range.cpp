#include <vector>
#include <cstdio>

int main(int argc, char** argv) {
    fprintf(stdout, "Vector example\n");

    std::vector<int> v = {10, 20, 30, 40};
    // The following will use Argument Dependent Lookup (ADL) 
    // The compile looks for begin in the current scope but there is no such function.
    // Then it looks a the type v which is std::vector and will look in its namespace.
    // That will match std::begin so the compile will use that.
    auto it1 = begin(v) + 0;
    printf("%d\n", *it1);

    int arr[] = {100, 200, 300, 400};
    // Notice that we can use an array with std::begin. But had we used v.begin()
    // which a int array does not have we would have get a compile error.
    // Since ADL will use the type's namespace to try to find the begin function
    // we have specify the following using directive because int is a fundamental type
    // and does not live in a namespace.
    using std::begin;
    auto it2 = begin(arr);
    for (; it2 != std::end(arr); ++it2) {
        printf("%d\n", *it2);
    }

    return 0;
}

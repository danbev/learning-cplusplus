#include <memory>
#include <iostream>
#include <vector>

int main() {
    // Create an allocator for integers
    std::allocator<int> alloc;
    
    // Allocate memory for 5 integers (doesn't construct them)
    int* ptr = alloc.allocate(5);

    ::new(ptr)   int(1);
    ::new(ptr+1) int(2);
    ::new(ptr+2) int(3);
    ::new(ptr+3) int(4);
    ::new(ptr+4) int(5);
    printf("Allocated memory at: %p\n", static_cast<void*>(ptr));
    for (int i = 0; i < 5; ++i) {
        std::cout << ptr[i] << " ";
    }
    printf("\n");
    alloc.destroy(ptr + 0);
    alloc.destroy(ptr + 1);
    alloc.destroy(ptr + 2);
    alloc.destroy(ptr + 3);
    alloc.destroy(ptr + 4);

    // just an example of using the locality hint parameter even though it 
    // does nothing unless we are using C++98 I think.
    int* ptr2 = alloc.allocate(5, ptr);
    
    // Construct objects in the allocated memory
    alloc.construct(ptr + 0, 42);
    alloc.construct(ptr + 1, 100);
    alloc.construct(ptr + 2, 200);
    
    // Use the objects
    std::cout << ptr[0] << ", " << ptr[1] << ", " << ptr[2] << std::endl;
    
    // Destroy objects (calls destructors)
    alloc.destroy(ptr + 0);
    alloc.destroy(ptr + 1);
    alloc.destroy(ptr + 2);
    
    // Deallocate memory
    alloc.deallocate(ptr, 5);
    
    return 0;
}

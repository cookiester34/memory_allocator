#include <iostream>
#include "memory/public/allocator.h"

int main()
{
    std::cout << "Starting Program \n";

    memory::allocator allocator(99);

    int* int_ptr = allocator.getMemory<int>(10);

    std::cout << allocator.void_ptr << "\n";
    std::cout << int_ptr << "\n";

    int* int_ptr2 = allocator.getMemory<int>(5);

    std::cout << int_ptr2 << "\n";

    allocator.freeMemory(int_ptr2, 5);

    int_ptr2 = allocator.getMemory<int>(5);

    std::cout << int_ptr2 << "\n";
}
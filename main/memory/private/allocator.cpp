#include <iostream>
#include "../public/allocator.h"

namespace memory
{
    allocator::allocator(int size)
    :size(size)
    {
        u8* u8_ptr = (u8*)malloc(size);

        for (u64 i = 0; i < size; i++)
        {
            u8_ptr[i] = 0;
        }
        
        void_ptr = (void*)u8_ptr;
    }
    
    allocator::~allocator()
    {
        free(void_ptr);
    }
}
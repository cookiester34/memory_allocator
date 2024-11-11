#pragma once

#include <iostream>

using u64 = uint64_t;
using u8 = uint8_t;

namespace memory
{
    class allocator
    {
    public:
        void* void_ptr = nullptr;
        int head = 0;
        u64 size = 0;
    public:
        allocator(int);
        ~allocator();

        template <typename T>
        [[nodiscard]]T* getMemory(int desired_size)
        {
            if (head > size) return nullptr;

            constexpr int type_size = sizeof(T);
            int required_size = type_size * desired_size;

            u8* u8_ptr = (u8*)void_ptr;
            int next_head = head + (head % alignof(T));

            bool found_space = false;
            while (next_head <= size && !found_space)
            {
                for (u64 i = 0; i < required_size; i++)
                {
                    if (u8_ptr[next_head + i] != 0)
                    {
                        next_head = head + i + 1;
                        break;
                    }

                    if (i == required_size - 1)
                    {
                        found_space = true;
                    }
                }
            }

            if (!found_space) return nullptr;

            if (head == next_head)
            {
                head += required_size;
            }
            
            return (T*)&u8_ptr[next_head];
        }

        template <typename T>
        void freeMemory(T* ptr, int memory_size)
        {
            u64 ptr_position = (u8*)ptr - (u8*)void_ptr;
            std::cout << ptr_position << "\n";

            u8* u8_ptr = (u8*)void_ptr;
            for (u64 i = 0; i < memory_size * sizeof(T); i++)
            {
                u8_ptr[ptr_position + i] = 0;
            }

            if (head > ptr_position)
            {
                head = ptr_position;
            }
        }
    };
}
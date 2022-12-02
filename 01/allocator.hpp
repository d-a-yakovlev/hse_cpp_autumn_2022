#pragma once

#include <iostream>

class Allocator
{
public:
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    ~Allocator();
private:
    char* memoryBlock;
    size_t maxSize, offset;
};
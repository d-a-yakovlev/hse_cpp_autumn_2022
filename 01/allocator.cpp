#include "allocator.hpp"

void
Allocator::makeAllocator(size_t maxSize)
{
    delete[] Allocator::memoryBlock;
    if ( maxSize  == 0 ) {
        Allocator::maxSize = 0;
        return;
    }
    
    Allocator::offset = 0;
    Allocator::maxSize = maxSize;
    Allocator::memoryBlock = new char[maxSize];
}

char*
Allocator::alloc(size_t size)
{
    if ( ( Allocator::offset + size > Allocator::maxSize )
        || ( size == 0) )
        return nullptr;

    // char* currentBlock = Allocator::memoryBlock + Allocator::offset;
    // Allocator::offset += size;
    
    // return currentBlock;

    Allocator::offset += size;
    return Allocator::memoryBlock + Allocator::offset - size;
}

void
Allocator::reset()
{
    Allocator::offset = 0;
}

Allocator::~Allocator() 
{
    delete[] Allocator::memoryBlock;
}
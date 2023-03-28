#include "allocator.hpp"

void
Allocator::makeAllocator(size_t maxSize)
{
    if ( this->memoryBlock != nullptr ) {
        delete[] this->memoryBlock;
        this->memoryBlock = nullptr;
    }
    
    if ( maxSize  == 0 ) {
        this->maxSize = 0;
        return;
    }
    
    this->offset = 0;
    this->maxSize = maxSize;
    this->memoryBlock = new char[maxSize];
}

char*
Allocator::alloc(size_t size)
{
    if ( ( this->offset + size > this->maxSize )
        || ( size == 0) )
        return nullptr;

    char* currentBlock = this->memoryBlock + this->offset;
    this->offset += size;
    
    return currentBlock;
}

void
Allocator::reset()
{
    this->offset = 0;
}

Allocator::~Allocator() 
{ 
    delete[] this->memoryBlock;
}
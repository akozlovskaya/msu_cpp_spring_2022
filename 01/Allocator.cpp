#include "Allocator.hpp"

/******Allocator constructor and destructor******/

Allocator::Allocator() : free_size(0), cap(0), data(nullptr), offset(nullptr)
{}

Allocator::~Allocator()
{
    if (data != nullptr) delete data;
    data = nullptr;
}


/******Allocator extra methods******/

size_t Allocator::get_free_size()
{
    return free_size;
}



/******Allocator methods******/

void Allocator::makeAllocator(size_t maxSize)
{
    if (data != nullptr) delete data;   
    data = new char(maxSize);
    offset = data;
    free_size = maxSize;
    cap = maxSize;
}


char* Allocator::alloc(size_t size)
{
    if (size > get_free_size()) return nullptr;
    
    free_size -= size;
    
    char *ret;
    ret = offset;
    offset += size;
    
    return ret;
}


void Allocator::reset()
{
    offset = data;
    free_size = cap;
}

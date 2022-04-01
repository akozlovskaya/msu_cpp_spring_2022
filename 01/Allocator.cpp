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
    if (maxSize < 1) throw std::invalid_argument{"makeAllocator"};
    if (data != nullptr) delete data;    
    data = new char(maxSize);
    offset = data;
    free_size = maxSize;
    cap = maxSize;
}


char* Allocator::alloc(size_t size)
{
    if (size < 1) throw std::invalid_argument{"alloc"};
    if (data == nullptr) throw std::logic_error{"alloc: no makeAllocator"};
    
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

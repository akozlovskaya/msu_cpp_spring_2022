#pragma once

#include <cstddef>
#include <iostream>

class Allocator
{
private:
    size_t free_size;
    size_t cap;
    char *data;
    char *offset;
    
public:
    Allocator();

    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    
    size_t get_free_size();
    
    ~Allocator();
};


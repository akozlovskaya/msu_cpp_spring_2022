#include <iostream>

#include "sort.hpp"

int main() {
    
    size_t limit = 8 * 1024 * 1024;
    std::string filename, result;
    std::cout << "Enter filename: ";
    getline(std::cin, filename);
    std::cout << "Enter result name: ";
    getline(std::cin, result);
    threads_sort(filename, limit, result);
    return 0;
}
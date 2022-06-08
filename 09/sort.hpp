#include <thread>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <vector>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem::v1;

void insertion_sort(std::vector<uint64_t> &);
void split_into_files(const std::string, const std::string, const std::string, const size_t);
void merge_and_sort(std::fstream &, std::vector<uint64_t> &, uint64_t, uint64_t, uint64_t);
void sort(const std::string, const size_t);
void merge_two_files(const std::string, const std::string, const std::string);
void threads_sort(const std::string, size_t, const std::string);
#pragma once

#include <iostream>
#include <cstring>
#include <string>

class brackets_imbalance: public std::invalid_argument
{
public:

    brackets_imbalance() : std::invalid_argument{""} {}

    brackets_imbalance(const std::string &error)
        : std::invalid_argument{error.c_str()} {}

};

class wrong_str_format: public std::invalid_argument
{
public:

    wrong_str_format() : std::invalid_argument{""} {}

    wrong_str_format(const std::string &error)
        : std::invalid_argument{error.c_str()} {}

};

class too_many_arguments: public std::invalid_argument
{
public:

    too_many_arguments() : std::invalid_argument{""} {}

    too_many_arguments(const std::string &error)
        : std::invalid_argument{error.c_str()} {}
};
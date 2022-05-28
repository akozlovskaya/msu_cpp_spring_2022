#pragma once

#include <iostream>
#include <cstring>
#include <sstream>

#include "custom_exceptions.hpp"

bool correct_brackets(const std::string&);

template <class T>
std::string to_string(T& val) {
    std::stringstream ss;
    ss << val;
    return ss.str();
}

template <class T>
void replace_i(std::string &str, int i, T&& val)
{
    if (str.find_first_of("{}") != std::string::npos) {
        throw wrong_str_format();
    }
    // if something went wrong...
    if (to_string(val) != "Last arg") {
        throw std::runtime_error("Wrong last arg");
    }
    if (i < 0) {
        throw std::runtime_error("Wrong index");
    }
}

template <class T, class... Args>
void replace_i(std::string &str, int i, T&& val, Args&&... args)
{
    if (str.find_first_of("{}") == std::string::npos) {
        throw too_many_arguments();
    }
    size_t pos = 0;
    std::string substr = "{" + std::to_string(i) + "}";
    std::string replacer = to_string(val);
    while ((pos = str.find(substr, pos)) != std::string::npos)
    {
        str.replace(pos, substr.size(), replacer);
        pos += replacer.size();
    }
    replace_i(str, i+1, args...);
}

template <class... Args>
std::string format(const std::string& str, Args&&... args)
{
    if (!correct_brackets(str)) {
        throw brackets_imbalance();
    }
    if (str.find_first_of("{}") == std::string::npos) {
        if (sizeof...(args) != 0) {
            throw too_many_arguments();
        } else {
            return str;
        }
    }
    std::string new_str(str);
    replace_i(new_str, 0, args..., "Last arg");
    return new_str;
}

#pragma once

#include <iostream>
#include <cstring>
#include <sstream>

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
    size_t pos = 0;
    std::string substr = "{" + std::to_string(i) + "}";
    std::string replacer = to_string(val);
    while ((pos = str.find(substr, pos)) != std::string::npos)
    {
        str.replace(pos, substr.size(), replacer);
        pos += replacer.size();
    }
}

template <class T, class... Args>
void replace_i(std::string &str, int i, T&& val, Args&&... args)
{
    size_t pos = 0;
    std::string substr = "{"+std::to_string(i)+"}";
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
        throw std::invalid_argument{"Invalid format"};
    }
    std::string new_str(str);
    replace_i(new_str, 0, args...);
    if (new_str.find_first_of("{}") != std::string::npos) {
        throw std::invalid_argument{"Invalid format"};
    }
    return new_str;
}

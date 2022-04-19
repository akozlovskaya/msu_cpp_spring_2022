#pragma once

#include <cstddef>
#include <iostream>

using func_str = void (*)(const std::string &);
using func_digit = void (*)(uint64_t);

struct Token
{
	std::string data;
    char type = 'd';
};

class TokenParser
{
private:
    func_str StartCallbackFunc = nullptr;
    func_str EndCallbackFunc = nullptr;
    func_digit DigitCallbackFunc = nullptr;
    func_str StringCallbackFunc = nullptr;
public:

    TokenParser() = default;

    void SetStartCallback(func_str);
    void SetEndCallback(func_str);
    void SetStringCallback(func_str);
    void SetDigitCallback(func_digit);
    
    void Parse(const std::string &);
    void token_processing(struct Token &);
};

const std::string MAX = "18446744073709551615";

#include "Parser.hpp"
void TokenParser::Parse(const std::string &str)
{
    
    if (StartCallbackFunc != nullptr) StartCallbackFunc("\nStart parsing!");
    
    struct Token token;
    
    for (auto it=str.begin(); it!=str.end(); ++it) {
        if (isspace(*it)) {
            token_processing(token);
            continue;
        }
        token.data += *it;
        if (!std::isdigit(*it)) token.type = 's';
    }
    token_processing(token);
    
    if (EndCallbackFunc != nullptr) EndCallbackFunc("Finish parsing!\n");
}

void TokenParser::token_processing(struct Token &tok) {
    if (tok.data.empty()) return;
    if (tok.type == 'd') {
        if (tok.data.size() > MAX.size() ||
           (tok.data.size() == MAX.size() && tok.data > MAX)) {
            tok.type = 's';
        } else if (DigitCallbackFunc != nullptr) {
            DigitCallbackFunc(atoi(tok.data.c_str()));
        }
    }
    
    if (tok.type == 's') {
        if (StringCallbackFunc != nullptr) StringCallbackFunc(tok.data);
    }
    
    tok.type = 'd';
    tok.data.clear();
}

void TokenParser::SetDigitCallback(func_digit func)
{
    DigitCallbackFunc = func;
}

void TokenParser::SetStringCallback(func_str func)
{
    StringCallbackFunc = func;
}

void TokenParser::SetStartCallback(func_str func)
{
    StartCallbackFunc = func;
}

void TokenParser::SetEndCallback(func_str func)
{
    EndCallbackFunc = func;
}

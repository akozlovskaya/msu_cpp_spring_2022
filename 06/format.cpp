#include "format.hpp"

bool correct_brackets(const std::string& str)
{
     bool closed = true;
     for (auto it = str.begin(); it < str.end(); it++) {
        if (*it == '{') {
            if (!closed) {
                return false;
            }
            closed = false;
        }
        if (*it == '}') {
            if (closed) {
                return false;
            }
            closed = true;
        }
      }
      return closed;
}

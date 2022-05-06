#include "format.hpp"


int main()
{
    std::string new_s;
    try {
        new_s = format("aaa {0} b{bb", 1);
    } catch(std::invalid_argument &ex) {
        std::cout << ex.what() << std::endl;
    } catch(...) {
        std::cout << "some exception" << std::endl;
    }
    return 0;
}

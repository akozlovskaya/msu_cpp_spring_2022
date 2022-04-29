#include <iostream>
#include <sstream>
#include "Serializer.hpp"


struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
    
    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(&a, &b, &c);
    }
};

int main()
{
    std::stringstream ss;
    Data x { 17, true, 2 };
    Data y { 11, false, 21 };
    
    Serializer serializer(ss);
    serializer.save(x);
    serializer.save(y);
    
    Data m { 0, false, 0 };

    Deserializer deserializer(ss);
    const Error err = deserializer.load(m);
    
    std::cout << "err = " << (err != Error::NoError) << std::endl;
    std::cout << m.a << std::endl;
    std::cout << m.b << std::endl;
    std::cout << m.c << std::endl;
    
    const Error err2 = deserializer.load(m);
    
    std::cout << "err2 = " << (err2 != Error::NoError) << std::endl;
    std::cout << m.a << std::endl;
    std::cout << m.b << std::endl;
    std::cout << m.c << std::endl;
    
    return 0;
}

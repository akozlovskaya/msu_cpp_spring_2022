#include <iostream>
#include <gtest/gtest.h>

#include "Serializer.hpp"


class TestFoo : public ::testing::Test
{
protected:
	void SetUp()
	{
        std::cout << "SetUp" << std::endl;
	}
	void TearDown()
	{
        std::cout << "TearDown" << std::endl;
	}
};


struct Data1
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


struct Data2
{
    uint64_t a;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a);
    }
    
    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(&a);
    }
};


struct Data3
{
    bool a;
    bool b;
    bool c;
    bool d;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c, d);
    }
    
    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(&a, &b, &c, &d);
    }
};


TEST_F(TestFoo, test_correct_load)
{
    std::stringstream stream;
    Data1 x { 17, true, 2 };
    Data2 y { 11 };
    Data3 z { true, true, false, true };
    
    Data1 m { 0, false, 0 };
    Data2 n { 0 };
    Data3 k { false, false, false, false };
    
    Serializer serializer(stream);
    Deserializer deserializer(stream);
    
    serializer.save(x);
    serializer.save(y);
    serializer.save(z);
    
    const Error err1 = deserializer.load(m);
    const Error err2 = deserializer.load(n);
    const Error err3 = deserializer.load(k);
    
    ASSERT_EQ(err1, Error::NoError);
    ASSERT_EQ(err2, Error::NoError);
    ASSERT_EQ(err3, Error::NoError);
    
    ASSERT_EQ(x.a, m.a);
    ASSERT_EQ(x.b, m.b);
    ASSERT_EQ(x.c, m.c);
    
    ASSERT_EQ(y.a, n.a);
    
    ASSERT_EQ(z.a, k.a);
    ASSERT_EQ(z.b, k.b);
    ASSERT_EQ(z.c, k.c);
    ASSERT_EQ(z.d, k.d);
    
    //проверка что исходные структуры не изменились
    ASSERT_EQ(x.a, 17);
    ASSERT_EQ(x.b, true);
    ASSERT_EQ(x.c, 2);
    
    ASSERT_EQ(y.a, 11);
    
    ASSERT_EQ(z.a, true);
    ASSERT_EQ(z.b, true);
    ASSERT_EQ(z.c, false);
    ASSERT_EQ(z.d, true);
}

TEST_F(TestFoo, test_incorrect_load)
{
    std::stringstream stream;
    Data2 data_int { 11 };
    Data3 data_bool { true, true, false, false };
    
    Serializer serializer(stream);
    Deserializer deserializer(stream);
    
    serializer.save(data_int);
    const Error err1 = deserializer.load(data_bool);
    ASSERT_EQ(err1, Error::CorruptedArchive);
    ASSERT_EQ(data_bool.a, true);
    
    serializer.save(data_bool);
    const Error err2 = deserializer.load(data_int);
    ASSERT_EQ(err2, Error::CorruptedArchive);
    ASSERT_EQ(data_int.a, 11);
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

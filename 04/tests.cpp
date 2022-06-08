#include <iostream>
#include <gtest/gtest.h>
#include <sstream>

#include "BigInt.hpp"

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

std::string
to_str(const BigInt& bigint)
{
    std::stringstream stream;
    stream << bigint;
    return stream.str();
}

TEST_F(TestFoo, test_constructor)
{
    //обычные числа
    BigInt a("123456789012345678901234567890");
    BigInt b("-123456789012345678901234567890");
    BigInt c(12345);
    BigInt d(-12345);
    BigInt e = 12345;
    BigInt f = -12345;
    //однозначные числа
    BigInt a1("1");
    BigInt b1("-1");
    BigInt c1(1);
    BigInt d1(-1);
    BigInt e1 = 1;
    BigInt f1 = -1;
    //нули
    BigInt g1("0");
    BigInt g2(0);
    BigInt g3 = 0;

    ASSERT_EQ(to_str(a), "123456789012345678901234567890");
    ASSERT_EQ(to_str(b), "-123456789012345678901234567890");
    ASSERT_EQ(to_str(c), "12345");
    ASSERT_EQ(to_str(d), "-12345");
    ASSERT_EQ(to_str(e), "12345");
    ASSERT_EQ(to_str(f), "-12345");
    ASSERT_EQ(to_str(a1), "1");
    ASSERT_EQ(to_str(b1), "-1");
    ASSERT_EQ(to_str(c1), "1");
    ASSERT_EQ(to_str(d1), "-1");
    ASSERT_EQ(to_str(e1), "1");
    ASSERT_EQ(to_str(f1), "-1");
    ASSERT_EQ(to_str(g1), "0");
    ASSERT_EQ(to_str(g2), "0");
    ASSERT_EQ(to_str(g2), "0");
    
    BigInt new_a(a);
    ASSERT_EQ(to_str(new_a), "123456789012345678901234567890");
    ASSERT_EQ(to_str(a), "123456789012345678901234567890");

    BigInt new_g3(g3);
    ASSERT_EQ(to_str(new_g3), "0");
    ASSERT_EQ(to_str(g3), "0");

    BigInt new_d(d);
    ASSERT_EQ(to_str(new_d), "-12345");
    ASSERT_EQ(to_str(d), "-12345");
}

TEST_F(TestFoo, test_addition_subtraction)
{
    std::stringstream stream;

    // a + b = 0
    BigInt a("123456789012345678901234567890");
    BigInt b("-123456789012345678901234567890");
    ASSERT_EQ(to_str(a + b), "0");
    /*
    a < b < 0
    a < 0 < b
    b < 0 < a
    b < a < 0
    0 < a < b
    0 < b < a
    */

    a = -123;
    b = -103;
    ASSERT_EQ(to_str(a + b), "-226");
    ASSERT_EQ(to_str(a - b), "-20");
    a = -123;
    b = 103;
    ASSERT_EQ(to_str(a + b), "-20");
    ASSERT_EQ(to_str(a - b), "-226");
    a = 123;
    b = -103;
    ASSERT_EQ(to_str(a + b), "20");
    ASSERT_EQ(to_str(a - b), "226");
    a = -123;
    b = -203;
    ASSERT_EQ(to_str(a + b), "-326");
    ASSERT_EQ(to_str(a - b), "80");
    a = 123;
    b = 203;
    ASSERT_EQ(to_str(a + b), "326");
    ASSERT_EQ(to_str(a - b), "-80");
    a = 123;
    b = 103;
    ASSERT_EQ(to_str(a + b), "226");
    ASSERT_EQ(to_str(a - b), "20");

    /*
    BigInt + int32_t
    BigInt - int32_t
    */

    a = 15;
    ASSERT_EQ(to_str(a + 5), "20");
    ASSERT_EQ(to_str(a - 5), "10");
    ASSERT_EQ(to_str(a - 55), "-40");
    
    /* интересный случай */
    a = 999999999;
    b = 1;
    ASSERT_EQ(to_str(a + b), "1000000000");
}

TEST_F(TestFoo, test_multiplication)
{
    std::stringstream stream;

    BigInt a("20");
    BigInt b("15");
    ASSERT_EQ(to_str(a*b), "300");

    b = -15;
    ASSERT_EQ(to_str(a*b), "-300");

    b = 0;
    ASSERT_EQ(to_str(a*b), "0");

    a = -30;
    b = 5;
    ASSERT_EQ(to_str(a*b), "-150");

    a = -30;
    b = -10;
    ASSERT_EQ(to_str(a*b), "300");


    a = 3;
    ASSERT_EQ(to_str(a*5), "15");
    ASSERT_EQ(to_str(a*(-2)), "-6");

    a = -30;
    ASSERT_EQ(to_str(a*5), "-150");
    ASSERT_EQ(to_str(a*(-2)), "60");
}


TEST_F(TestFoo, test_unary_minus)
{
    BigInt a("20");
    BigInt b = -a;
    BigInt c = -b;
    ASSERT_EQ(to_str(b), "-20");
    ASSERT_EQ(to_str(c), "20");
}

TEST_F(TestFoo, test_comparison)
{
    /*
    c < d < 0
    c < 0 < d
    d < 0 < c
    d < c < 0
    0 < c < d
    0 < d < c
    |c| == |d|, |c| != |d|
    */

    BigInt c = -123;
    BigInt d = -103;
    ASSERT_EQ(c < d, true);
    ASSERT_EQ(c <= d, true);
    ASSERT_EQ(c > d, false);
    ASSERT_EQ(c >= d, false);
    ASSERT_EQ(c == d, false);
    ASSERT_EQ(c != d, true);

    c = -123;
    d = 103;
    ASSERT_EQ(c < d, true);
    ASSERT_EQ(c <= d, true);
    ASSERT_EQ(c > d, false);
    ASSERT_EQ(c >= d, false);
    ASSERT_EQ(c == d, false);
    ASSERT_EQ(c != d, true);

    c = 123;
    d = -103;
    ASSERT_EQ(c < d, false);
    ASSERT_EQ(c <= d, false);
    ASSERT_EQ(c > d, true);
    ASSERT_EQ(c >= d, true);
    ASSERT_EQ(c == d, false);
    ASSERT_EQ(c != d, true);

    c = -123;
    d = -203;
    ASSERT_EQ(c < d, false);
    ASSERT_EQ(c <= d, false);
    ASSERT_EQ(c > d, true);
    ASSERT_EQ(c >= d, true);
    ASSERT_EQ(c == d, false);
    ASSERT_EQ(c != d, true);

    c = 123;
    d = 203;
    ASSERT_EQ(c < d, true);
    ASSERT_EQ(c <= d, true);
    ASSERT_EQ(c > d, false);
    ASSERT_EQ(c >= d, false);
    ASSERT_EQ(c == d, false);
    ASSERT_EQ(c != d, true);

    c = 123;
    d = 103;
    ASSERT_EQ(c < d, false);
    ASSERT_EQ(c <= d, false);
    ASSERT_EQ(c > d, true);
    ASSERT_EQ(c >= d, true);
    ASSERT_EQ(c == d, false);
    ASSERT_EQ(c != d, true);

    c = 120;
    d = 120;
    ASSERT_EQ(c < d, false);
    ASSERT_EQ(c <= d, true);
    ASSERT_EQ(c > d, false);
    ASSERT_EQ(c >= d, true);
    ASSERT_EQ(c == d, true);
    ASSERT_EQ(c != d, false);

    c = 120;
    d = -120;
    ASSERT_EQ(c < d, false);
    ASSERT_EQ(c <= d, false);
    ASSERT_EQ(c > d, true);
    ASSERT_EQ(c >= d, true);
    ASSERT_EQ(c == d, false);
    ASSERT_EQ(c != d, true);

    c = -120;
    d = -120;
    ASSERT_EQ(c < d, false);
    ASSERT_EQ(c <= d, true);
    ASSERT_EQ(c > d, false);
    ASSERT_EQ(c >= d, true);
    ASSERT_EQ(c == d, true);
    ASSERT_EQ(c != d, false);

    c = -120;
    d = 120;
    ASSERT_EQ(c < d, true);
    ASSERT_EQ(c <= d, true);
    ASSERT_EQ(c > d, false);
    ASSERT_EQ(c >= d, false);
    ASSERT_EQ(c == d, false);
    ASSERT_EQ(c != d, true);
}

TEST_F(TestFoo, test_operators)
{
    BigInt a("20");
    BigInt b;
    b = a;
    
    ASSERT_EQ(to_str(b), "20");
    ASSERT_EQ(to_str(a), "20");
    
    a = -20;
    b = a;
    ASSERT_EQ(to_str(b), "-20");
    ASSERT_EQ(to_str(a), "-20");
    
    a = a;
    ASSERT_EQ(to_str(a), "-20");
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

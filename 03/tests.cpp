#include <iostream>
#include <gtest/gtest.h>
#include <fstream>

#include "Matrix.hpp"

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

TEST_F(TestFoo, test_constructor)
{
    const size_t rows = 5;
    const size_t cols = 3;

    Matrix m(rows, cols);

    ASSERT_EQ(m.get_row_num(),  5);
    ASSERT_EQ(m.get_col_num(), 3);
}

TEST_F(TestFoo, test_сompare)
{
    const size_t rows = 5;
    const size_t cols = 3;

    Matrix m(rows, cols);
    
    m[1][2] = 5;
    ASSERT_EQ(m[1][2], 5);
    
    double x = m[4][1];
    ASSERT_EQ(x,  0);
    
    Matrix m1(rows, cols);
    ASSERT_NE(m, m1);
    ASSERT_NE(m == m1, true);
    ASSERT_EQ(m != m1, true);
}

TEST_F(TestFoo, test_mult)
{
    Matrix m(5, 3);
    Matrix m1(5, 3);
    
    m[1][2] = 12;
    m[1][3] = 18;
    
    m1[1][2] = 4;
    m1[1][3] = 6;
    m1 *= 3;
    ASSERT_EQ(m, m1);
}

TEST_F(TestFoo, test_sum)
{
    Matrix m(5, 3);
    Matrix m1(5, 3);
    
    m[1][2] = 1;
    m[1][3] = 1;
    
    m1[1][2] = -1;
    m1[1][3] = 1;
    std::cout << m1 + m << std::endl;
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

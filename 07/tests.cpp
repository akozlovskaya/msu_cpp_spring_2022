#include <iostream>
#include <gtest/gtest.h>
#include <fstream>

#include "Vector.hpp"

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

TEST_F(TestFoo, test_correct)
{
    /*-------------------push_back, size, capacity-------------------*/
    Vector<int> vector(4);
    ASSERT_EQ(vector.size(), 0);
    ASSERT_EQ(vector.capacity(), 4);
    vector.push_back(6);
    vector.push_back(7);
    vector.push_back(11);
    ASSERT_EQ(vector.size(), 3);
    ASSERT_EQ(vector.capacity(), 4);
    ASSERT_EQ(vector[0], 6);
    ASSERT_EQ(vector[1], 7);
    ASSERT_EQ(vector[2], 11);

    /*--------------------------emplace_back-------------------------*/
    vector.emplace_back(15);
    ASSERT_EQ(vector.size(), 3);
    ASSERT_EQ(vector[2], 15);

    /*----------------------------pop_back---------------------------*/
    ASSERT_EQ(vector.pop_back(), 15);
    ASSERT_EQ(vector.size(), 2);

    /*-----------------------------resize----------------------------*/
    vector.resize(10);
    ASSERT_EQ(vector[0], 6);
    ASSERT_EQ(vector[1], 7);
    for (int i = 2; i < 10; ++i) {
        ASSERT_EQ(vector[i], 0);
    }
    ASSERT_EQ(vector.size(), 10);

    vector.resize(20, 15);
    ASSERT_EQ(vector[0], 6);
    ASSERT_EQ(vector[1], 7);
    for (int i = 2; i < 10; ++i) {
        ASSERT_EQ(vector[i], 0);
    }
    for (int i = 10; i < 20; ++i) {
        ASSERT_EQ(vector[i], 15);
    }
    ASSERT_EQ(vector.size(), 20);

    /*----------------------------reserve----------------------------*/
    vector.reserve(100);
    ASSERT_EQ(vector[0], 6);
    ASSERT_EQ(vector[1], 7);
    for (int i = 2; i < 10; ++i) {
        ASSERT_EQ(vector[i], 0);
    }
    for (int i = 10; i < 20; ++i) {
        ASSERT_EQ(vector[i], 15);
    }
    ASSERT_EQ(vector.size(), 20);
    ASSERT_EQ(vector.capacity(), 100);

    /*----------------------------empty----------------------------*/
    ASSERT_FALSE(vector.empty());
    for (int i = 0; i < 20; ++i) {
        vector.pop_back();
    }
    ASSERT_TRUE(vector.empty());

    /*----------------------------clear----------------------------*/
    for (int i = 0; i < 20; ++i) {
        vector.push_back(i);
    }
    ASSERT_EQ(vector.size(), 20);
    vector.clear();
    ASSERT_TRUE(vector.empty());
}

TEST_F(TestFoo, test_iter)
{
    Vector<int> vector;
    for (int i = 0; i < 20; ++i) {
        vector.push_back(i);
    }
    int k = 0;
    for (auto it = vector.begin(); it != vector.end(); ++it) {
        ASSERT_EQ(*it, k++);
    }
    k = 19;
    for (auto it = vector.rbegin(); it != vector.rend(); ++it) {
        ASSERT_EQ(*it, k--);
    }
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

#include <iostream>

#include <gtest/gtest.h>


#include "Allocator.hpp"

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

TEST_F(TestFoo, test_alloc)
{
    Allocator my_allocator;
    my_allocator.makeAllocator(10);
    
    char *a = my_allocator.alloc(5);
    char *b = my_allocator.alloc(6);
    char *c = my_allocator.alloc(3);
    
    ASSERT_NE(a, nullptr);
    ASSERT_EQ(b, nullptr);
    ASSERT_NE(c, nullptr);
}

TEST_F(TestFoo, test_reset)
{
    Allocator my_allocator;
    my_allocator.makeAllocator(10);
    
    char *a = my_allocator.alloc(5);
    my_allocator.reset();
    char *b = my_allocator.alloc(10);
    
    ASSERT_EQ(a, b);
    
    my_allocator.makeAllocator(25);
    my_allocator.reset();
}

//test only for valgrind
TEST_F(TestFoo, test_make)
{
    Allocator my_allocator;
    my_allocator.makeAllocator(10);
    my_allocator.makeAllocator(15);
    const char *b = my_allocator.alloc(5);
    b = "abcd";
    
    my_allocator.makeAllocator(25);
    my_allocator.reset();
    b = my_allocator.alloc(5);
    b = "abcd";
    
    // to avoid -Werror=unused-variable
    ASSERT_NE(nullptr, b);
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

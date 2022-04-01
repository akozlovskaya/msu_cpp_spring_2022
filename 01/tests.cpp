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
    
    ASSERT_NE(my_allocator.alloc(5), nullptr);
    ASSERT_EQ(my_allocator.alloc(6), nullptr);
    ASSERT_NE(my_allocator.alloc(3), nullptr);
    my_allocator.reset();
    ASSERT_NE(my_allocator.alloc(3), my_allocator.alloc(3));
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
    
    ASSERT_NE(my_allocator.alloc(25), nullptr);
    my_allocator.reset();
}


TEST_F(TestFoo, test_invalid_arg)
{
    Allocator my_allocator;
    ASSERT_ANY_THROW(my_allocator.makeAllocator(0));
    
    my_allocator.makeAllocator(10);
    ASSERT_ANY_THROW(my_allocator.alloc(0));
}


TEST_F(TestFoo, bad_order)
{
    Allocator my_allocator;
    ASSERT_ANY_THROW(my_allocator.alloc(1));
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

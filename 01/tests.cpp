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

// make(1), alloc(1), alloc(1)
TEST_F(TestFoo, bound_cond)
{
    Allocator my_allocator;
    char *a;
    my_allocator.makeAllocator(1);
    
    a = my_allocator.alloc(1);
    ASSERT_NE(a, nullptr);
    
    ASSERT_NO_THROW(a = my_allocator.alloc(1));
    ASSERT_EQ(a, nullptr);
}

// make(50), alloc(20), alloc(30), alloc(1), reset(), alloc(50)
TEST_F(TestFoo, method_chain)
{
    Allocator my_allocator;
    char *a;
    
    my_allocator.makeAllocator(50);
    
    a = my_allocator.alloc(20);
    ASSERT_NE(a, nullptr);
    
    a = my_allocator.alloc(30);
    ASSERT_NE(a, nullptr);
    
    ASSERT_NO_THROW(a = my_allocator.alloc(1));
    ASSERT_EQ(a, nullptr);
    
    my_allocator.reset();
    
    ASSERT_NO_THROW(a = my_allocator.alloc(50));
    ASSERT_NE(a, nullptr);
}

// char* p1 = alloc->alloc(10); char* p2 = alloc->alloc(10); p1 - p2 == ?
TEST_F(TestFoo, pointers)
{
    Allocator *my_allocator = new Allocator();
    my_allocator->makeAllocator(50);
    
    char* p1 = my_allocator->alloc(10);
    char* p2 = my_allocator->alloc(10);
    ASSERT_EQ(p2-p1, 10);
    
    delete my_allocator;
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

#include <iostream>
#include <gtest/gtest.h>
#include <fstream>

#include "format.hpp"

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

TEST_F(TestFoo, test_1)
{
    ASSERT_EQ(format("{1}+{1} = {0}", 2, "one"), "one+one = 2");
    ASSERT_EQ(format("{0}", "val_0", "val_1"), "val_0");
    ASSERT_EQ(format("{1}", "val_0", "val_1"), "val_1");
    std::string str = "{2} aaa {3} bbb {0} ccc {1} ddd {0} eee {0}";
    ASSERT_EQ(format(str, 0, 1, 2, 3), "2 aaa 3 bbb 0 ccc 1 ddd 0 eee 0");
    
}


TEST_F(TestFoo, test_2)
{
    EXPECT_THROW(format("{{0}}", 1, 2), std::invalid_argument);
    EXPECT_THROW(format("{0} text {} text {1}", 1, 2), std::invalid_argument);
    EXPECT_THROW(format("{12} text {0} text {1}", 1, 2), std::invalid_argument);
    EXPECT_THROW(format("text {a} text", "val_a"), std::invalid_argument);
    EXPECT_THROW(format("text {-1} text", "val_1"), std::invalid_argument);
    EXPECT_THROW(format("text te{xt", 1), std::invalid_argument);
    EXPECT_THROW(format("te}xt text", 1), std::invalid_argument);
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

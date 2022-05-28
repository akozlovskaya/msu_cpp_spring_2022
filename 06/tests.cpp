#include <iostream>
#include <gtest/gtest.h>
#include <fstream>

#include "format.hpp"
#include "custom_exceptions.hpp"

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
    // пустая строка
    ASSERT_EQ(format(""), "");
    // строка без форматирования
    ASSERT_EQ(format("string without formatting"), "string without formatting");
    ASSERT_EQ(format("{1}+{1} = {0}", 2, "one"), "one+one = 2");
    // единичный аргумент
    ASSERT_EQ(format("{0}", "val_0"), "val_0");
    ASSERT_EQ(format("{1}", "val_0", "val_1"), "val_1");
    // множество {N}
    ASSERT_EQ(format("{0}{0}{0}{0}{0}", "val_0"), "val_0val_0val_0val_0val_0");
    ASSERT_EQ(format("{0} aaa {0} bbb {0}{0} ccc {0}", "val_0"), "val_0 aaa val_0 bbb val_0val_0 ccc val_0");
    // мои примеры
    std::string str = "{2} aaa {3} bbb {0} ccc {1} ddd {0} eee {0}";
    ASSERT_EQ(format(str, 0, 1, 2, 3), "2 aaa 3 bbb 0 ccc 1 ddd 0 eee 0");

}


TEST_F(TestFoo, test_incorrect)
{
    EXPECT_THROW(format("{{0}}", 1, 2), brackets_imbalance);
    EXPECT_THROW(format("{0} text {} text {1}", 1, 2), wrong_str_format);
    EXPECT_THROW(format("{12} text {0} text {1}", 1, 2), wrong_str_format);
    EXPECT_THROW(format("text {a} text", "val_a"), wrong_str_format);
    EXPECT_THROW(format("text {18446744073709551616} text", "val_a"), wrong_str_format);
    EXPECT_THROW(format("text {1str} text", "val_a"), wrong_str_format);
    EXPECT_THROW(format("text {-1} text", "val_1"), wrong_str_format);
    EXPECT_THROW(format("text te{xt", 1), brackets_imbalance);
    EXPECT_THROW(format("te}xt text", 1), brackets_imbalance);
    EXPECT_THROW(format("{2} text {0} text {1}", 1, 2), wrong_str_format);
    EXPECT_THROW(format("{2} text {0} text {1}", 1, 2, 3, 4, 5), too_many_arguments);

    EXPECT_THROW(format("{{0}}", 1, 2), std::invalid_argument);
    EXPECT_THROW(format("{0} text {} text {1}", 1, 2), std::invalid_argument);
    EXPECT_THROW(format("{12} text {0} text {1}", 1, 2), std::invalid_argument);
    EXPECT_THROW(format("text {a} text", "val_a"), std::invalid_argument);
    EXPECT_THROW(format("text {18446744073709551616} text", "val_a"), std::invalid_argument);
    EXPECT_THROW(format("text {1str} text", "val_a"), std::invalid_argument);
    EXPECT_THROW(format("text {-1} text", "val_1"), std::invalid_argument);
    EXPECT_THROW(format("text te{xt", 1), std::invalid_argument);
    EXPECT_THROW(format("te}xt text", 1), std::invalid_argument);
    EXPECT_THROW(format("{2} text {0} text {1}", 1, 2), std::invalid_argument);
    EXPECT_THROW(format("{2} text {0} text {1}", 1, 2, 3, 4, 5), std::invalid_argument);
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

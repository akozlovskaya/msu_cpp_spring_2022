#include <iostream>
#include <gtest/gtest.h>
#include <fstream>

#include "Parser.hpp"

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
    
/* тесты парсинга пустой строки, строки только из пробельных символов,
односимвольных строк-токенов ("1", "a"), строк с токенами вида 42str,
токены для проверки макс значения uint64: 2^64-1 и 2^64, 2^65, смешанные строки
с проверкой количества вызова разных колбеков */

int start_end_num = 0;
int dig_num = 0;
int str_num = 0;

static void print_msg(const std::string &msg) {
    std::cout << msg << "\n";
    start_end_num++;
}
static void dig_token_func(uint64_t tok) {
    std::cout << "Digit token: " << tok << "\n";
    dig_num++;
}
static void str_token_func(const std::string &tok) {
    std::cout << "String token: " << tok << "\n";
    str_num++;
}

TEST_F(TestFoo, test_set)
{
    TokenParser parser;
    parser.SetStartCallback(print_msg);
    parser.SetEndCallback(print_msg);
    parser.SetDigitCallback(dig_token_func);
    parser.SetStringCallback(str_token_func);
    
    parser.Parse("");
    ASSERT_EQ(start_end_num, 2);
    ASSERT_EQ(dig_num, 0);
    ASSERT_EQ(str_num, 0);
    start_end_num = 0, dig_num = 0, str_num = 0;
    
    parser.Parse("   ");
    ASSERT_EQ(start_end_num, 2);
    ASSERT_EQ(dig_num, 0);
    ASSERT_EQ(str_num, 0);
    start_end_num = 0, dig_num = 0, str_num = 0;
    
    parser.Parse("1");
    ASSERT_EQ(start_end_num, 2);
    ASSERT_EQ(dig_num, 1);
    ASSERT_EQ(str_num, 0);
    start_end_num = 0, dig_num = 0, str_num = 0;
    
    parser.Parse("a");
    ASSERT_EQ(start_end_num, 2);
    ASSERT_EQ(dig_num, 0);
    ASSERT_EQ(str_num, 1);
    start_end_num = 0, dig_num = 0, str_num = 0;
    
    parser.Parse("18446744073709551615");    
    ASSERT_EQ(start_end_num, 2);
    ASSERT_EQ(dig_num, 1);
    ASSERT_EQ(str_num, 0);
    start_end_num = 0, dig_num = 0, str_num = 0;
    
    parser.Parse("18446744073709551616");
    ASSERT_EQ(start_end_num, 2);
    ASSERT_EQ(dig_num, 0);
    ASSERT_EQ(str_num, 1);
    start_end_num = 0, dig_num = 0, str_num = 0;
    
    parser.Parse("36893488147419103232");
    ASSERT_EQ(start_end_num, 2);
    ASSERT_EQ(dig_num, 0);
    ASSERT_EQ(str_num, 1);
    start_end_num = 0, dig_num = 0, str_num = 0;
    
    parser.Parse("118446744073709551616");
    ASSERT_EQ(start_end_num, 2);
    ASSERT_EQ(dig_num, 0);
    ASSERT_EQ(str_num, 1);
    start_end_num = 0, dig_num = 0, str_num = 0;
    
    parser.Parse("qs 23	ed3  5  3dw\nkem 2e 	\t	e");
    ASSERT_EQ(start_end_num, 2);
    ASSERT_EQ(dig_num, 2);
    ASSERT_EQ(str_num, 6);
}

/* те же тесты без установленных колбеков */

TEST_F(TestFoo, test_no_set)
{
    TokenParser parser;
    parser.Parse("");
    parser.Parse("   ");
    parser.Parse("1");
    parser.Parse("a");
    parser.Parse("18446744073709551615");
    parser.Parse("18446744073709551616");
    parser.Parse("36893488147419103232");
    parser.Parse("118446744073709551616");
    parser.Parse("qs 23	ed3  5  3dw\nkem 2e 	\t	e");
}

/* те же тесты с установкой колбеков равных nullptr */

TEST_F(TestFoo, test_set_nullptr)
{
    TokenParser parser;
    parser.SetStartCallback(nullptr);
    parser.SetEndCallback(nullptr);
    parser.SetDigitCallback(nullptr);
    parser.SetStringCallback(nullptr);
    parser.Parse("");
    parser.Parse("   ");
    parser.Parse("1");
    parser.Parse("a");
    parser.Parse("18446744073709551615");
    parser.Parse("18446744073709551616");
    parser.Parse("36893488147419103232");
    parser.Parse("118446744073709551616");
    parser.Parse("qs 23	ed3  5  3dw\nkem 2e 	\t	e");
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

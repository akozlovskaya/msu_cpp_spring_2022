#include <iostream>
#include <gtest/gtest.h>
#include <fstream>

#include "sort.hpp"


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
    size_t limit = 1024;
    std::string res = "result.bin";
    threads_sort("example.bin", limit, res);
    
    // должно получиться 1 2 3 ... 1024
    std::ifstream f1(res, std::ios::in | std::ios::binary);
    int64_t x;
    for (int64_t i = 0; i < fs::file_size(res) / 8; ++i) {
        f1.read((char*)& x, sizeof x);
        ASSERT_EQ(x, i + 1);
    }
    f1.close();
    
    res = "result2.bin";
    threads_sort("example2.bin", limit, res);
    
    // должно получиться 0 0 .. 0 0 1 1 .. 1 1 2 2 .. 2 2 ..... 31 .. 31 31
    // каждое число повторяется 256 раз
    std::ifstream f2(res, std::ios::in | std::ios::binary);
    for (int64_t i = 0; i < fs::file_size(res) / 8; ++i) {
        f2.read((char*)& x, sizeof x);
        ASSERT_EQ(x, i / 256);
    }
    f2.close();
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

#include <iostream>
#include <gtest/gtest.h>
#include <fstream>
#include <unistd.h>

#include "ThreadPool.hpp"

struct A {};

void foo(const A&) {}

uint64_t sleepy_max(uint64_t a, uint64_t b, uint64_t c)
{
    sleep(5);
	if (a >= b) {
        return a >= c ? a : c;
    } else {
        return b >= c ? b : c;
    }
}

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
    ThreadPool pool(8);

    auto task1 = pool.exec(foo, A());
    task1.get();
    
    auto task2 = pool.exec([]() { return 1; });
    ASSERT_EQ(task2.get(), 1);
    
    uint64_t SIZE = 2634;
    ThreadPool pool_2(SIZE);
    std::vector <uint64_t> numbers(3 * SIZE);

    // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 0 1 2 3 ...
    for (int i = 0; i < numbers.size(); ++i)
        numbers[i] = i % 18;
    
	std::vector <std::future <uint64_t>> result;
    // считаем среднее в каждой тройке
	for (size_t i = 0; i < numbers.size(); i += 3)
		result.push_back(pool_2.exec(
                                        sleepy_max,
                                        numbers[i],
                                        numbers[i + 1],
                                        numbers[i + 2]
                                    ));
    
    // должна получиться последовательность 2 5 8 11 14 17 2 5 8 11 14 17 ...
	for (size_t i = 0; i < result.size(); ++i)
		ASSERT_EQ(result[i].get(), (i % 6) * 3 + 2);
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

CC=g++-11
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

.PHONY: test clean

all: test_bin

test_bin: Vector.hpp tests.cpp
	$(CC) $(FLAGS) tests.cpp -o test_bin $(TEST_LIBS)

test: test_bin
	./test_bin

clean:
	rm -f *.o main test_bin
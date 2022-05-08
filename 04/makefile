CC=g++-11
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

.PHONY: test clean

all: main test_bin

main: BigInt.o main.cpp
	$(CC) $(FLAGS) BigInt.o main.cpp -o main

BigInt.o: BigInt.cpp BigInt.hpp
	$(CC) $(FLAGS) BigInt.cpp -c

test_bin: BigInt.o tests.cpp
	$(CC) $(FLAGS) BigInt.o tests.cpp -o test_bin $(TEST_LIBS)

test: test_bin
	./test_bin

clean:
	rm -f *.o main test_bin
CC=g++-11
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

.PHONY: test clean

all: main test_bin

main: Matrix.o main.cpp
	$(CC) $(FLAGS) Matrix.o main.cpp -o main

Matrix.o: Matrix.cpp Matrix.hpp
	$(CC) $(FLAGS) Matrix.cpp -c

test_bin: Matrix.o tests.cpp
	$(CC) $(FLAGS) Matrix.o tests.cpp -o test_bin $(TEST_LIBS)

test:
	./test_bin

clean:
	rm -f *.o main test_bin
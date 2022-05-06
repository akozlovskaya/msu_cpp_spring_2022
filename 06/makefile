CC=g++-11
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

.PHONY: test clean

all: main test_bin

main: format.o main.cpp
	$(CC) $(FLAGS) format.o main.cpp -o main

format.o: format.cpp format.hpp
	$(CC) $(FLAGS) format.cpp -c

test_bin: format.o tests.cpp
	$(CC) $(FLAGS) format.o tests.cpp -o test_bin $(TEST_LIBS)

test: test_bin
	./test_bin

clean:
	rm -f *.o main test_bin
CC=g++-11
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

.PHONY: test clean

all: main test_bin

main: Serializer.o main.cpp
	$(CC) $(FLAGS) Serializer.o main.cpp -o main

Serializer.o: Serializer.cpp Serializer.hpp
	$(CC) $(FLAGS) Serializer.cpp -c

test_bin: Serializer.o tests.cpp
	$(CC) $(FLAGS) Serializer.o tests.cpp -o test_bin $(TEST_LIBS)

test: test_bin
	./test_bin

clean:
	rm -f *.o main test_bin
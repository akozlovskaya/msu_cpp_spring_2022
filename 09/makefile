CC=g++
FLAGS=-std=c++1z -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread  -lstdc++fs

all: test_bin

test: test_bin
	./test_bin

test_bin: sort.o tests.cpp
	$(CC) sort.o tests.cpp -o test_bin $(TEST_LIBS)

main: sort.o main.cpp
	$(CC) sort.o main.cpp -o main $(TEST_LIBS)

sort.o: sort.cpp sort.hpp
	$(CC) $(FLAGS) sort.cpp -c

clean:
	rm -rf *.o test_bin

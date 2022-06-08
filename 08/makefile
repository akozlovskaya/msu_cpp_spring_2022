CC=g++
FLAGS=-std=c++1z -Wall -pedantic -Wextra -Werror -c
TEST_LIBS=-lgtest_main -lgtest -lpthread

all: test_bin

test: test_bin
	./test_bin

test_bin: ThreadPool.o tests.cpp
	$(CC) ThreadPool.o tests.cpp -o test_bin $(TEST_LIBS)

ThreadPool.o: ThreadPool.cpp ThreadPool.hpp
	$(CC) $(FLAGS) ThreadPool.cpp -c

clean:
	rm -rf *.o test_bin

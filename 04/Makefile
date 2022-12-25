CC=g++
FLAGS= -Wall -pedantic -Werror -Wextra
TEST_LIB=-std=c++20 -lgtest -lgtest_main -lpthread

all: big_int test_bin

big_int: big_int.cpp big_int.hpp
	$(CC) $(FLAGS) -c big_int.cpp

test_bin: big_int.o tests.cpp
	$(CC) $(FLAGS) big_int.o tests.cpp -o test_bin $(TEST_LIB)

test:
	./test_bin

clean:
	rm -f *.o test_bin
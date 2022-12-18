CC=g++
FLAGS= -Wall -pedantic -Werror -Wextra
TEST_LIB=-std=c++20 -lgtest -lgtest_main -lpthread

all: matrix test_bin

matrix: matrix.cpp matrix.hpp
	$(CC) $(FLAGS) -c matrix.cpp

test_bin: matrix.o tests.cpp
	$(CC) $(FLAGS) matrix.o tests.cpp -o test_bin $(TEST_LIB)

test:
	./test_bin

clean:
	rm -f *.o test_bin
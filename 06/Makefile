CC=g++
FLAGS= -Wall -pedantic -Werror -Wextra
TEST_LIB=-std=c++20 -lgtest -lgtest_main -lpthread

all: format test_bin

format: format.cpp format.hpp
	$(CC) $(FLAGS) -c format.cpp

test_bin: format.o tests.cpp
	$(CC) $(FLAGS) format.o tests.cpp -o test_bin $(TEST_LIB)

test:
	./test_bin

clean:
	rm -f *.o test_bin
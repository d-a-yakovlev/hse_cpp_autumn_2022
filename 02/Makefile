CC=g++
FLAGS= -Wall -pedantic -Werror -Wextra
TEST_LIB=-std=c++20 -lgtest -lgtest_main -lpthread

all: tokenParser test_bin

tokenParser: tokenParser.cpp tokenParser.hpp
	$(CC) $(FLAGS) -c tokenParser.cpp

test_bin: tokenParser.o tests.cpp
	$(CC) $(FLAGS) tokenParser.o tests.cpp -o test_bin $(TEST_LIB)

test:
	./test_bin

clean:
	rm -f *.o test_bin

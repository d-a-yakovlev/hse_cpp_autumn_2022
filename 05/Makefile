CC=g++
FLAGS= -Wall -pedantic -Werror -Wextra
TEST_LIB=-std=c++20 -lgtest -lgtest_main -lpthread

all: serializer test_bin

serializer: serializer.cpp serializer.hpp
	$(CC) $(FLAGS) -c serializer.cpp

test_bin: serializer.o tests.cpp
	$(CC) $(FLAGS) serializer.o tests.cpp -o test_bin $(TEST_LIB)

test:
	./test_bin

clean:
	rm -f *.o test_bin
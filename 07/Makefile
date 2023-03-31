CC=g++
FLAGS= -Wall -pedantic -Werror -Wextra
TEST_LIB=-std=c++20 -lgtest -lgtest_main -lpthread

all:  test_bin # tree_avl

# tree_avl: tree_avl.cpp tree_avl.hpp
# 	$(CC) $(FLAGS) -c tree_avl.cpp

test_bin: tree_avl.hpp tests.cpp
	$(CC) $(FLAGS) tests.cpp -o test_bin $(TEST_LIB)

test:
	./test_bin

clean:
	rm -f *.o test_bin
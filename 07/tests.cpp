#include <iostream>
#include <gtest/gtest.h>

#include "tree_avl.hpp"

class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};


TEST(TestTree, test_basic)
{
    TreeAVL<int, int> tree;
    tree.insert(std::make_pair<int,int>(2, 2));
    tree.insert(std::make_pair<int,int>(1, 1));
    tree.insert(std::make_pair<int,int>(3, 3));
    tree.insert(std::make_pair<int,int>(4, 4));

    tree.print();
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

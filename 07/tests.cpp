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
    TreeAVL tree;
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

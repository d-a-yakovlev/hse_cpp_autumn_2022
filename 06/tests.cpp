#include <iostream>
#include <gtest/gtest.h>

#include "format.hpp"

class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};


TEST(TestFormat, test_basic)
{
    auto text = format("{1}+{1} = {0}", 2, "one");
    ASSERT_EQ(text, "one+one = 2");
}
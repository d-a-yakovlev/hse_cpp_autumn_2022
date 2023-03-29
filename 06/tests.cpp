#include <iostream>
#include <gtest/gtest.h>

#include "format.hpp"

class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};


TEST(TestFormat, test_basic_and_HBO)
{
    {
        auto text = cute::format("{1}+{1} = {0}", 2, "one");
        ASSERT_EQ("one+one = 2", text);
    }
    {
        auto text = cute::format("{0}+{2} in {1}", "Walter", "Lab", "Jesse");
        ASSERT_EQ("Walter+Jesse in Lab", text);
    }
    {
        auto text = cute::format("{1}+{2} ? of course {0}", "Saul", "Better", "Call");
        ASSERT_EQ("Better+Call ? of course Saul", text);
    }
    {
        auto text = cute::format("{1}{2}.state == {0}", "charState.Alive", "John", "Snow");
        ASSERT_EQ("JohnSnow.state == charState.Alive", text);
    }
    {
        auto text = cute::format("{1}_{0} in {2}", "Soprano", "Tony", "Depression");
        ASSERT_EQ("Tony_Soprano in Depression", text);
    }
}


TEST(TestFormat, test_basic_twin)
{
    {
        auto text = cute::format("{1}+{1} = {0}", 2, "one");
        ASSERT_EQ(text, "one+one = 2");
    }
    {
        auto text = cute::format("{1}+{1} = {0}", 2, "one");
        ASSERT_EQ(text, "one+one = 2");
    }
}


TEST(TestFormat, test_incorrect_brackets_use)
{
    {
        try {
            auto text = cute::format("{Jesse}+{Jesse} = {Walter}", 2, "one");
        }
        catch(cute::Error err) {
            ASSERT_EQ(cute::Error::BadFormat, err);
        }
        
    }

    {
        try {
            auto text = cute::format("{42}+{42} = {42}", 2, "one");
        }
        catch(cute::Error err) {
            ASSERT_EQ(cute::Error::ArgumentException, err);
        }
    }

    {
        try {
            auto text = cute::format("{0}+{1} = {2}", 42);
        }
        catch(cute::Error err) {
            ASSERT_EQ(cute::Error::ArgumentException, err);
        }
    }
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

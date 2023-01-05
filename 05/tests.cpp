#include <iostream>
#include <gtest/gtest.h>

#include "serializer.hpp"

class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};


TEST(TestSerializer, test_debug_what_stream_contain)
{
    DataA x { 33, false, 400 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    std::string data;
    while (stream >> data) {
        std::cout << data << " ";
    }
    std::cout << std::endl;
}


TEST(TestSerializer, test_serializer_DataA)
{
    DataA x { 33, false, 400 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    DataA y { 0, true, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    ASSERT_EQ(err, Error::NoError);

    ASSERT_EQ(x.a, y.a);
    ASSERT_EQ(x.b, y.b);
    ASSERT_EQ(x.c, y.c);
}


TEST(TestSerializer, test_serializer_DataB)
{
    DataB x {  true, true, 1337 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    DataB y { false, false, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    ASSERT_EQ(err, Error::NoError);

    ASSERT_EQ(x.a, y.a);
    ASSERT_EQ(x.b, y.b);
    ASSERT_EQ(x.c, y.c);
}


TEST(TestSerializer, test_serializer_bad_data)
{
    DataA x {  0, true, 1917 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    DataB y { false, 0, 1 };

    Deserializer deserializer(stream);
    
    Error err = deserializer.load(y);

    ASSERT_EQ(err, Error::CorruptedArchive);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

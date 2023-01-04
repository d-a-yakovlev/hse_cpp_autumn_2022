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
    Data x { 33, false, 400 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    std::string data;
    while (stream >> data) {
        std::cout << data << " ";
    }
    std::cout << std::endl;
}


TEST(TestSerializer, test_serializer_Data_1)
{
    Data x { 33, false, 400 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data y { 0, true, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    ASSERT_EQ(err, Error::NoError);

    ASSERT_EQ(x.a, y.a);
    ASSERT_EQ(x.b, y.b);
    ASSERT_EQ(x.c, y.c);
}


TEST(TestSerializer, test_serializer_Data_2)
{
    Data x {  42, true, 1337 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data y { 0, false, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    ASSERT_EQ(err, Error::NoError);

    ASSERT_EQ(x.a, y.a);
    ASSERT_EQ(x.b, y.b);
    ASSERT_EQ(x.c, y.c);
}


TEST(TestSerializer, test_serializer_bad_data_1)
{
    Data x {  322, true, 777 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data y { true, false, true };

    Deserializer deserializer(stream);
    
    Error err;
    try {
        err = deserializer.load(y);
    } catch (Error catched_err) {
        ASSERT_EQ(err, Error::CorruptedArchive);
        ASSERT_EQ(catched_err, Error::CorruptedArchive);

        std::cout << "in catch debug" << std::endl;
        if (catched_err == Error::CorruptedArchive) {
            std::cout << "Error::CorruptedArchive catched" << std::endl;
        } else {
            std::cout << "Some error catched" << std::endl;
        }
    }

    ASSERT_EQ(err, Error::NoError);
    if (err == Error::NoError) {
        std::cout << "Error::NoError catched" << std::endl;
    } else {
        std::cout << "Some error catched" << std::endl;
    }
}


TEST(TestSerializer, test_serializer_bad_data_2)
{
    Data x {  0, true, 1917 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data y { false, 0, true };

    Deserializer deserializer(stream);
    
    Error err;
    try {
        err = deserializer.load(y);
    } catch (Error catched_err) {
        ASSERT_EQ(err, Error::CorruptedArchive);
        ASSERT_EQ(catched_err, Error::CorruptedArchive);

        if (catched_err == Error::CorruptedArchive)
            std::cout << "Error::CorruptedArchive catched" << std::endl;
    }

    if (err == Error::NoError) {
        std::cout << "Error::NoError catched" << std::endl;
    } else {
        std::cout << "Some error catched" << std::endl;
    }
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

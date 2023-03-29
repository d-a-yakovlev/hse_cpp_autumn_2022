#include <iostream>
#include <limits>

#include <gtest/gtest.h>

#include "serializer.hpp"
#include "test_data.hpp"


class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};


void showStreamContent(std::stringstream& stream)
{
    std::string data;
    while (stream >> data) {
        std::cout << data << " ";
    }
    std::cout << std::endl;
}


TEST(TestSerializer, test_save)
{
    DataA x { 33, false, 400 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    ASSERT_EQ("33 false 400", stream.str());
    // showStreamContent(stream);
}


TEST(TestSerializer, test_serializer_DataA)
{
    DataA x { 33, false, 400 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);
    ASSERT_EQ("33 false 400", stream.str());

    DataA y { 0, true, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);
    ASSERT_EQ(stream.tellg(), -1);

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
    ASSERT_EQ("true true 1337", stream.str());

    DataB y { false, false, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);
    ASSERT_EQ(stream.tellg(), -1);

    ASSERT_EQ(err, Error::NoError);

    ASSERT_EQ(x.a, y.a);
    ASSERT_EQ(x.b, y.b);
    ASSERT_EQ(x.c, y.c);
}


TEST(TestSerializer, test_serializer_bad_data_AB)
{
    DataA x {  0, true, 1917 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);
    ASSERT_EQ("0 true 1917", stream.str());

    DataB y { false, 0, 1 };

    Deserializer deserializer(stream);
    
    Error err = deserializer.load(y);
    ASSERT_NE(stream.tellg(), -1);

    ASSERT_EQ(y.a, false);
    ASSERT_EQ(y.b, false);
    ASSERT_EQ(y.c, 1);

    ASSERT_EQ(err, Error::CorruptedArchive);
}


TEST(TestSerializer, test_serializer_bad_data_AC)
{
    DataA x {  42, true, 1917 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);
    ASSERT_EQ("42 true 1917", stream.str());

    DataC y { false, 0, 1 };

    Deserializer deserializer(stream);
    
    Error err = deserializer.load(y);
    ASSERT_NE(stream.tellg(), -1);

    ASSERT_EQ(y.a, 42);
    ASSERT_EQ(y.b, 0);
    ASSERT_EQ(y.c, 1);

    ASSERT_EQ(err, Error::CorruptedArchive);
}


TEST(TestSerializer, test_one_atr_bb)
{
    DataOneBool x {  true };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    DataOneBool y { false };

    Deserializer deserializer(stream);
    Error err = deserializer.load(y);
    ASSERT_EQ(stream.tellg(), -1);

    ASSERT_EQ(err, Error::NoError);

    ASSERT_EQ(x.a, y.a);
}


TEST(TestSerializer, test_one_atr_bu)
{
    DataOneBool x {  true };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    DataOneUint y { 42 };

    Deserializer deserializer(stream);
    Error err = deserializer.load(y);

    ASSERT_EQ(err, Error::CorruptedArchive);
}


TEST(TestSerializer, test_one_atr_ub)
{
    DataOneUint x {  42 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    DataOneBool y { false };

    Deserializer deserializer(stream);
    Error err = deserializer.load(y);

    ASSERT_EQ(err, Error::CorruptedArchive);
}


TEST(TestSerializer, test_one_atr_uu)
{
    DataOneUint x {  1337 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    DataOneUint y { 42 };

    Deserializer deserializer(stream);
    Error err = deserializer.load(y);
    ASSERT_EQ(stream.tellg(), -1);

    ASSERT_EQ(err, Error::NoError);

    ASSERT_EQ(x.a, y.a);
}


TEST(TestSerializer, test_one_atr_bu_overflow_u64)
{
    DataOneBool x( std::numeric_limits<uint64_t>::max() + 1 );

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);
    ASSERT_EQ("false", stream.str());

    DataOneUint y { std::numeric_limits<uint64_t>::max() };

    Deserializer deserializer(stream);
    Error err = deserializer.load(y);

    ASSERT_EQ(err, Error::CorruptedArchive);
}


TEST(TestSerializer, test_one_atr_ub_overflow_u64)
{
    DataOneUint x {  std::numeric_limits<uint64_t>::max() + 1 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);
    ASSERT_EQ("0", stream.str());

    DataOneBool y( std::numeric_limits<uint64_t>::max() );

    Deserializer deserializer(stream);
    Error err = deserializer.load(y);

    ASSERT_EQ(err, Error::CorruptedArchive);
}


TEST(TestSerializer, test_one_atr_uu_overflow_u64)
{
    DataOneUint x {  std::numeric_limits<uint64_t>::max() + 1 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);
    ASSERT_EQ("0", stream.str());

    DataOneUint y { std::numeric_limits<uint64_t>::max() };

    Deserializer deserializer(stream);
    Error err = deserializer.load(y);
    ASSERT_EQ(stream.tellg(), -1);

    ASSERT_EQ(err, Error::NoError);

    ASSERT_EQ(x.a, y.a);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

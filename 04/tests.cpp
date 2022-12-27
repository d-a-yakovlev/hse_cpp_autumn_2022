#include <iostream>
#include <gtest/gtest.h>

#include "big_int.hpp"

class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};

TEST(TestBigInt, test_functionality_and_show)
{
    BigInt a = BigInt(123);
    BigInt b = -456;
    BigInt c1 = a;
    BigInt c2 = BigInt(b);
    BigInt d = BigInt();
    BigInt e = BigInt("-123456789");
    BigInt f = BigInt("3221337");
    BigInt o1 = 123;
    BigInt o2 = 124;
    BigInt o3 = 122;

    std::cout << std::boolalpha << "a :" << std::endl;
    a.show_debug();
    std::cout << "b :" << std::endl;
    b.show_debug();
    std::cout << "c1 :" << std::endl;
    c1.show_debug();
    std::cout << "c2 :" << std::endl;
    c2.show_debug();
    std::cout << "d :" << std::endl;
    d.show_debug();
    std::cout << "e :" << std::endl;
    e.show_debug();
    std::cout << "f :" << std::endl;
    f.show_debug();

    std::cout << "o1 :" << std::endl;
    o1.show_debug();
    std::cout << "o2 :" << std::endl;
    o2.show_debug();
    std::cout << "o3 :" << std::endl;
    o3.show_debug();

    std::cout << "o1 > o1 = " << (o1 > o1) << std::endl;
    std::cout << "o1 > o2 = " << (o1 > o2) << std::endl;
    std::cout << "o3 > o1 = " << (o3 > o1) << std::endl;
    std::cout << "o2 > o1 = " << (o2 > o1) << std::endl;
    std::cout << "o1 > o3 = " << (o1 > o3) << std::endl;
    std::cout << "o3 > o2 = " << (o3 > o2) << std::endl;
    std::cout << "o2 > o3 = " << (o2 > o3) << std::endl;

    BigInt res11 = o1 + o1;
    BigInt res12 = o1 + o2;
    BigInt res31 = o3 + o1;
    BigInt res2_1 = o2 - o1;
    BigInt res1_3 = o1 - o3;
    BigInt res3_2 = o3 - o2;
    BigInt res2_3 = o2 - o3;

    std::cout << "o1 + o1 = " << res11 << std::endl;
    std::cout << "o1 + o2 = " << res12 << std::endl;
    std::cout << "o3 + o1 = " << res31 << std::endl;
    std::cout << "o2 - o1 = " << res2_1 << std::endl;
    std::cout << "o1 - o3 = " << res1_3 << std::endl;
    std::cout << "o3 - o2 = " << res3_2 << std::endl;
    res3_2.show_debug();
    std::cout << "o2 - o3 = " << res2_3 << std::endl;


    std::cout << "a > a = " << (a > a) << std::endl;
    std::cout << "a > b = " << (a > b) << std::endl;
    std::cout << "b > a = " << (b > a) << std::endl;
    std::cout << "a > f = " << (a > f) << std::endl;
    std::cout << "f > a = " << (f > a) << std::endl;
    std::cout << "b > e = " << (b > e) << std::endl;
    std::cout << "e > b = " << (e > b) << std::endl;

    BigInt m1 = std::move(e);
    BigInt m2 = std::move(f);

    std::cout << "m1 :" << std::endl;
    m1.show_debug();
    std::cout << "m2 :" << std::endl;
    m2.show_debug();
    std::cout << "e :" << std::endl;
    e.show_debug();
    std::cout << "f :" << std::endl;
    f.show_debug();


    std::cout << "9999999999-199999999 = " << (BigInt("9999999999") - BigInt("199999999")) << std::endl;
    std::cout << "199999999-9999999999 = " << (BigInt("199999999")-BigInt("9999999999")) << std::endl;

    BigInt mult1 = BigInt("1111111111111111111111111111111111111111111");
    BigInt mult2 = BigInt("1000000000000000000000000000000000000000000");

    std::cout << "mult1 * mult2 = " << ((-mult1) * (-mult2)) << std::endl;
    ASSERT_EQ(((-mult1) * (-mult2)).to_string(), "1111111111111111111111111111111111111111111000000000000000000000000000000000000000000");
    mult1.show_debug();
    mult2.show_debug();
    std::cout << "mult1 * 7 = " << (mult1 * 7) << std::endl;
    ASSERT_EQ((mult1 * 7).to_string(), "7777777777777777777777777777777777777777777");
    std::cout << "mult2 * (-7) = " << (mult2 * (-7)) << std::endl;
    ASSERT_EQ((mult2 * (-7)).to_string(), "-7000000000000000000000000000000000000000000");
}


TEST(TestBigInt, test_constructor)
{
    BigInt a = BigInt("12345");
    BigInt b = BigInt();

    ASSERT_EQ(a.to_string(), "12345");
    ASSERT_EQ(b.to_string(), "");

    b = a;

    ASSERT_EQ(b.to_string(), a.to_string());

    BigInt c = BigInt();
    c = std::move(b);
    ASSERT_EQ(c.to_string(), a.to_string());
    ASSERT_EQ(b.to_string(), "");
}


TEST(TestBigInt, test_inequations_negatives)
{
    BigInt a = BigInt("1000000");
    BigInt aCopy = a;

    ASSERT_EQ(a==aCopy, 1);

    BigInt aGt = BigInt("1000001");

    ASSERT_EQ(a < aGt, 1);
    ASSERT_EQ(a <= aGt, 1);
    ASSERT_EQ(a <= a, 1);
    ASSERT_EQ(a > aGt, 0);
    ASSERT_EQ(a >= aGt, 0);
    ASSERT_EQ(a >= a, 1);
    ASSERT_EQ(aGt > a, 1);
    ASSERT_EQ(aGt < a, 0);

    ASSERT_EQ(-a < a, 1);
    ASSERT_EQ(-a < -(-a), 1);
}


TEST(TestBigInt, test_operations)
{
    BigInt a = BigInt("1000000");
    BigInt aGt1 = a + 1;
    BigInt _a1 = a - aGt1;

    BigInt ama = a * a;
    BigInt amaGt1 = a * aGt1;
    BigInt _a1ma = _a1 * a;

    ASSERT_EQ(aGt1.to_string(), "1000001");
    ASSERT_EQ(_a1.to_string(), "-1");
    ASSERT_EQ(ama.to_string(), "1000000000000");
    ASSERT_EQ(amaGt1.to_string(), "1000001000000");
    ASSERT_EQ(_a1ma.to_string(), "-1000000");
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

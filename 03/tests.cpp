#include <iostream>
#include <gtest/gtest.h>

#include "matrix.hpp"

class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};

TEST(TestMatrix, test_create_and_show)
{
    Matrix matrix = Matrix(3, 4);
    matrix.show_debug();

    matrix *= 7;
    matrix.show_debug();

    Matrix matrix_2 = Matrix(3, 4);
    matrix_2.show_debug();

    Matrix matrix_add_res = matrix + matrix_2;
    matrix_add_res.show_debug();

    std::cout << matrix_add_res[1][1] << std::endl;

    matrix_add_res[1][1] = 0;
    matrix_add_res.show_debug();

    std::cout << matrix_add_res << std::endl;

    std::cout << std::boolalpha << (matrix == matrix) << std::endl;
    std::cout << (matrix == matrix_2) << std::endl;
    std::cout << (matrix != matrix_2) << std::endl;
    std::cout << (matrix != matrix) << std::endl;

    std::cout << matrix[2][3] << std::endl;
}

TEST(TestMatrix, test_smth1)
{
    // ASSERT_TRUE( res != nullptr );
}

TEST(TestMatrix, test_smth2)
{
    // ASSERT_EQ( res, nullptr );
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
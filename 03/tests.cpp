#include <iostream>
#include <gtest/gtest.h>

#include "matrix.hpp"

class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};

TEST(TestMatrix, test_functionality_and_show)
{
    Matrix matrix = Matrix(3, 4);
    matrix.show_debug();

    // Проверка размеров, и значения по умолчению
    ASSERT_EQ( matrix.getRows(), 3 );
    ASSERT_EQ( matrix.getColumns(), 4 );
    ASSERT_EQ( matrix[0][0], 1 );

    // проверка умножения
    matrix *= 7;
    matrix.show_debug();
    ASSERT_EQ( matrix[0][0], 7 );

    Matrix matrix_2 = Matrix(3, 4);
    matrix_2.show_debug();

    // суммирование
    Matrix matrix_add_res = matrix + matrix_2;
    matrix_add_res.show_debug();
    ASSERT_EQ( matrix_add_res[0][0], 8 );

    // перезапись i, j
    matrix_add_res[1][1] = 0;
    matrix_add_res.show_debug();
    std::cout << matrix_add_res[1][1] << std::endl;
    ASSERT_EQ( matrix_add_res[1][1], 0 );

    std::cout << matrix_add_res << std::endl;

    // проверка на равенство и неравенство
    std::cout << std::boolalpha << (matrix == matrix) << std::endl;
    ASSERT_EQ( (matrix == matrix), 1 );
    std::cout << (matrix == matrix_2) << std::endl;
    ASSERT_EQ( (matrix == matrix_2), 0 );
    std::cout << (matrix != matrix_2) << std::endl;
    ASSERT_EQ( (matrix != matrix_2), 1 );
    std::cout << (matrix != matrix) << std::endl;
    ASSERT_EQ( (matrix != matrix), 0 );

    std::cout << matrix[2][3] << std::endl;
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
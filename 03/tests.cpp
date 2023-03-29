#include <iostream>
#include <sstream>

#include <gtest/gtest.h>

#include "matrix.hpp"

class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};

// TEST(TestMatrix, test_functionality_and_show)
// {
//     Matrix matrix = Matrix(3, 4);
//     matrix.show_debug();

//     // Проверка размеров, и значения по умолчению
//     ASSERT_EQ( matrix.getRows(), 3 );
//     ASSERT_EQ( matrix.getColumns(), 4 );
//     ASSERT_EQ( matrix[0][0], 1 );

//     // проверка умножения
//     matrix *= 7;
//     matrix.show_debug();
//     ASSERT_EQ( matrix[0][0], 7 );

//     Matrix matrix_2 = Matrix(3, 4);
//     matrix_2.show_debug();

//     // суммирование
//     Matrix matrix_add_res = matrix + matrix_2;
//     matrix_add_res.show_debug();
//     ASSERT_EQ( matrix_add_res[0][0], 8 );

//     // перезапись i, j
//     matrix_add_res[1][1] = 0;
//     matrix_add_res.show_debug();
//     std::cout << matrix_add_res[1][1] << std::endl;
//     ASSERT_EQ( matrix_add_res[1][1], 0 );

//     std::cout << matrix_add_res << std::endl;

//     // проверка на равенство и неравенство
//     std::cout << std::boolalpha << (matrix == matrix) << std::endl;
//     ASSERT_EQ( (matrix == matrix), 1 );
//     std::cout << (matrix == matrix_2) << std::endl;
//     ASSERT_EQ( (matrix == matrix_2), 0 );
//     std::cout << (matrix != matrix_2) << std::endl;
//     ASSERT_EQ( (matrix != matrix_2), 1 );
//     std::cout << (matrix != matrix) << std::endl;
//     ASSERT_EQ( (matrix != matrix), 0 );

//     std::cout << matrix[2][3] << std::endl;
// }


bool isMatrixSameToVector(const Matrix& mat, std::vector<std::vector<int>>&& vec)
{
    for (size_t i = 0; i < vec.size(); ++i)
    {
        for (size_t j=0; j < vec[0].size(); ++j)
        {
            if (mat[i][j] != vec[i][j]) {return false;}
        }
    }

    return true;
}


TEST(TestMatrix, test_shape)
{
    Matrix matrix = Matrix(3, 4);

    ASSERT_EQ( matrix.getRows(), 3 );
    ASSERT_EQ( matrix.getColumns(), 4 );
    ASSERT_EQ( matrix[0][0], 1 );
}


TEST(TestMatrix, test_element)
{
    Matrix matrix = Matrix(3, 4);

    matrix[1][1] = 0;
    ASSERT_EQ( matrix[1][1], 0 );

    matrix[0][0] = 42;
    ASSERT_EQ( matrix[0][0], 42 );
}


TEST(TestMatrix, test_ostream)
{
    Matrix matrix = Matrix(3, 4);

    std::stringstream stream;
    stream << matrix;

    std::string expected_str = "1\t1\t1\t1\n1\t1\t1\t1\n1\t1\t1\t1\n";
    ASSERT_EQ( expected_str, stream.str() );
}


TEST(TestMatrix, test_sum_base)
{
    {
        Matrix A = Matrix(3, 4);
        Matrix B = Matrix(3, 4);

        B[0][1] = 41;
        ASSERT_TRUE(
            isMatrixSameToVector( A+B, 
                                {{2, 42, 2, 2},
                                 {2,  2, 2, 2},
                                 {2,  2, 2, 2}} )
        );
    }
    {
        Matrix A = Matrix(4, 2);
        Matrix B = Matrix(4, 2);

        B *= -1;
        ASSERT_TRUE(
            isMatrixSameToVector( A+B,
                                {{0, 0},
                                 {0, 0},
                                 {0, 0},
                                 {0, 0}} )
        );
    }

}


TEST(TestMatrix, test_mult)
{
    Matrix A = Matrix(2, 2);
    
    A *= 42;
    ASSERT_TRUE(
        isMatrixSameToVector(
            A,
            {{42, 42},
             {42, 42}}
        )
    );

    A *= 0;
    ASSERT_TRUE(
        isMatrixSameToVector(
            A,
            {{0, 0},
             {0, 0}}
        )
    );
}


TEST(TestMatrix, test_mat_eq_ne)
{
    Matrix A = Matrix(2, 2);
    Matrix B = Matrix(2, 2);

    ASSERT_TRUE( A == B);

    A[0][0] = 42;
    ASSERT_TRUE( A != B);

    A[0][0] = 1;
    ASSERT_TRUE( A == B);
}


TEST(TestMatrix, test_shape_scalar)
{
    Matrix A = Matrix(1, 1);

    ASSERT_EQ( A.getRows(), 1 );
    ASSERT_EQ( A.getColumns(), 1 );

    A[0][0] = 40;
    ASSERT_EQ( A[0][0], 40 );

    Matrix B = Matrix(1, 1);
    B *= 2;

    ASSERT_TRUE(
        isMatrixSameToVector(
            B,
            {{2}}
        )
    );

    ASSERT_TRUE(
        isMatrixSameToVector(
            A+B,
            {{42}}
        )
    );
}


TEST(TestMatrix, test_shape_row)
{
    Matrix A = Matrix(1, 3);

    ASSERT_EQ( A.getRows(), 1 );
    ASSERT_EQ( A.getColumns(), 3 );

    A[0][0] = 40;
    ASSERT_EQ( A[0][0], 40 );

    Matrix B = Matrix(1, 3);
    B *= 2;

    ASSERT_TRUE(
        isMatrixSameToVector(
            B,
            {{2, 2, 2}}
        )
    );

    ASSERT_TRUE(
        isMatrixSameToVector(
            A+B,
            {{42, 3, 3}}
        )
    );
}


TEST(TestMatrix, test_shape_col)
{
    Matrix A = Matrix(3, 1);

    ASSERT_EQ( A.getRows(), 3 );
    ASSERT_EQ( A.getColumns(), 1 );

    A[0][0] = 40;
    ASSERT_EQ( A[0][0], 40 );

    Matrix B = Matrix(3, 1);
    B *= 2;

    ASSERT_TRUE(
        isMatrixSameToVector(
            B,
            {{2},
             {2},
             {2}}
        )
    );

    ASSERT_TRUE(
        isMatrixSameToVector(
            A+B,
            {{42},
             { 3},
             { 3}}
        )
    );
}


TEST(TestMatrix, test_OOR_get_element)
{
    size_t rows = 1;
    size_t cols = 4;

    Matrix matrix = Matrix(rows, cols);
    try {
        matrix[1][0] = 0;
    }
    catch (const std::out_of_range& oor) {
        std::string error_msg = oor.what();
        ASSERT_EQ(
            "First index out of range : 0 ... " + std::to_string(rows - 1),
            error_msg
        );
    }
    
    try {
        matrix[0][4] = 42;
    }
    catch (const std::out_of_range& oor) {
        std::string error_msg = oor.what();
        ASSERT_EQ(
            "Second index out of range : 0 ... " + std::to_string(cols - 1),
            error_msg
        );
    }

}


std::string format_error_msg(size_t row_1, size_t row_2, size_t col_1, size_t col_2)
{
    std::string result = "op1 shape = (" + 
                std::to_string(row_1) + ", " +
                std::to_string(col_1) + ") and " +
                "op2 shape = (" +
                std::to_string(row_2) + ", " +
                std::to_string(col_2) + ") must be same";

    return result;
}


TEST(TestMatrix, test_OOR_sum)
{
    {
        size_t row_1 = 2;
        size_t row_2 = 4;

        size_t col_1 = 2;
        size_t col_2 = 4;

        Matrix A = Matrix(row_1, col_1);
        Matrix B = Matrix(row_2, col_2);

        try {
            A+B;
        }
        catch (const std::out_of_range& oor) {
            std::string error_msg = oor.what();
            ASSERT_EQ(
                format_error_msg(row_1, row_2, col_1, col_2),
                error_msg
            );
        }
    }
    {
        size_t row_1 = 1;
        size_t row_2 = 4;

        size_t col_1 = 4;
        size_t col_2 = 1;

        Matrix A = Matrix(row_1, col_1);
        Matrix B = Matrix(row_2, col_2);

        try {
            A+B;
        }
        catch (const std::out_of_range& oor) {
            std::string error_msg = oor.what();
            ASSERT_EQ(
                format_error_msg(row_1, row_2, col_1, col_2),
                error_msg
            );
        }
    }
    {
        size_t row_1 = 2;
        size_t row_2 = 2;

        size_t col_1 = 1;
        size_t col_2 = 1;

        Matrix A = Matrix(row_1, col_1);
        Matrix B = Matrix(row_2, col_2);

        try {
            A+B;
        }
        catch (const std::out_of_range& oor) {
            std::string error_msg = oor.what();
            ASSERT_EQ(
                format_error_msg(row_1, row_2, col_1, col_2),
                error_msg
            );
        }
    }
}


TEST(TestMatrix, test_OOR_eq)
{
    {
        size_t row_1 = 2;
        size_t row_2 = 4;

        size_t col_1 = 2;
        size_t col_2 = 4;

        Matrix A = Matrix(row_1, col_1);
        Matrix B = Matrix(row_2, col_2);

        try {
            A==B;
        }
        catch (const std::out_of_range& oor) {
            std::string error_msg = oor.what();
            ASSERT_EQ(
                format_error_msg(row_1, row_2, col_1, col_2),
                error_msg
            );
        }
    }
    {
        size_t row_1 = 1;
        size_t row_2 = 4;

        size_t col_1 = 4;
        size_t col_2 = 1;

        Matrix A = Matrix(row_1, col_1);
        Matrix B = Matrix(row_2, col_2);

        try {
            A==B;
        }
        catch (const std::out_of_range& oor) {
            std::string error_msg = oor.what();
            ASSERT_EQ(
                format_error_msg(row_1, row_2, col_1, col_2),
                error_msg
            );
        }
    }
    {
        size_t row_1 = 2;
        size_t row_2 = 2;

        size_t col_1 = 1;
        size_t col_2 = 1;

        Matrix A = Matrix(row_1, col_1);
        Matrix B = Matrix(row_2, col_2);

        try {
            A==B;
        }
        catch (const std::out_of_range& oor) {
            std::string error_msg = oor.what();
            ASSERT_EQ(
                format_error_msg(row_1, row_2, col_1, col_2),
                error_msg
            );
        }
    }
}


TEST(TestMatrix, test_OOR_ne)
{
    {
        size_t row_1 = 2;
        size_t row_2 = 4;

        size_t col_1 = 2;
        size_t col_2 = 4;

        Matrix A = Matrix(row_1, col_1);
        Matrix B = Matrix(row_2, col_2);

        try {
            A!=B;
        }
        catch (const std::out_of_range& oor) {
            std::string error_msg = oor.what();
            ASSERT_EQ(
                format_error_msg(row_1, row_2, col_1, col_2),
                error_msg
            );
        }
    }
    {
        size_t row_1 = 1;
        size_t row_2 = 4;

        size_t col_1 = 4;
        size_t col_2 = 1;

        Matrix A = Matrix(row_1, col_1);
        Matrix B = Matrix(row_2, col_2);

        try {
            A!=B;
        }
        catch (const std::out_of_range& oor) {
            std::string error_msg = oor.what();
            ASSERT_EQ(
                format_error_msg(row_1, row_2, col_1, col_2),
                error_msg
            );
        }
    }
    {
        size_t row_1 = 2;
        size_t row_2 = 2;

        size_t col_1 = 1;
        size_t col_2 = 1;

        Matrix A = Matrix(row_1, col_1);
        Matrix B = Matrix(row_2, col_2);

        try {
            A!=B;
        }
        catch (const std::out_of_range& oor) {
            std::string error_msg = oor.what();
            ASSERT_EQ(
                format_error_msg(row_1, row_2, col_1, col_2),
                error_msg
            );
        }
    }
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
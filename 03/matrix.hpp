#pragma once

#include <iostream>
#include <string>


class Matrix
{
    class ProxyRow
    {
    public:
        int* data_;
        size_t size;
        ProxyRow();
        ~ProxyRow();
        /*
            Не меняет внутри себя объект, но предоставляет ссылку,
            данные в которой менять можно
        */
        int& operator[](size_t j) const;
    };
public:
    Matrix(size_t rows, size_t cols);
    ~Matrix();

    size_t getRows() const;
    size_t getColumns() const;

    ProxyRow& operator[](size_t i) const;

    Matrix& operator *= (int mult);
    Matrix operator + (const Matrix& rhs) const;
    bool operator == (const Matrix& rhs) const;
    bool operator != (const Matrix& rhs) const;


    void show_debug(); // show matrix in table view for debugging
private:
    //int id; 
    ProxyRow* rows_;
    size_t cRows, cCols;
};

std::ostream& operator << (std::ostream& out, const Matrix& matrix);
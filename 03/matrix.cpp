#include "matrix.hpp"


Matrix::ProxyRow::ProxyRow()
{
    std::cout << "Matrix::ProxyRow::ProxyRow" << this << std::endl;
}


Matrix::Matrix(size_t rows, size_t cols)
{
    std::cout << "Matrix::Matrix" << this << std::endl;
    this->cRows = rows;
    this->cCols = cols;
    
    this->rows_ = new ProxyRow[rows];
    for (size_t i=0; i < rows; ++i) {
        this->rows_[i].data_ = new int[cols];

        for (size_t j=0; j < cols; ++j) {
            this->rows_[i].data_[j] = 1;
            this->rows_[i].size = cols;
        }
    }
}


Matrix::ProxyRow::~ProxyRow()
{
    if (this->data_ != nullptr) {
        std::cout << "Matrix::ProxyRow::~ProxyRow" << this << std::endl;
        delete[] this->data_;
    }
}

Matrix::~Matrix()
{

    if (this->rows_ != nullptr) {
        std::cout << "Matrix::~Matrix" << this << std::endl;
        delete[] this->rows_;
    }
}


size_t
Matrix::getRows() const
{
    return this->cRows;
}


size_t
Matrix::getColumns() const
{
    return this->cCols;
}


int& Matrix::ProxyRow::operator[](size_t j) const
{
    if ( j > this->size-1 )
        throw std::out_of_range(
            "Second index out of range : 0 ... "+
            std::to_string(this->size - 1));

    return data_[j];
}


Matrix::ProxyRow& Matrix::operator[](size_t i) const
{
    if ( i > this->cRows-1 )
        throw std::out_of_range(
            "First index out of range : 0 ... "+
            std::to_string(this->cRows - 1));

    return rows_[i];
}


std::ostream& operator << (std::ostream& out, const Matrix& matrix)
{
    std::string result = "";
    for (size_t i=0; i < matrix.getRows(); ++i) {
        for (size_t j=0; j < matrix.getColumns(); ++j) {
            result += std::to_string(matrix[i][j]);
            if (j != matrix.getColumns() - 1)
                result += "\t";
        }
        result += "\n";
    }

    out << result;
    return out;
}


Matrix Matrix::operator + (const Matrix& rhs) const
{
    if (! (this->cRows == rhs.getRows() && this->cCols == rhs.getColumns()) )
        throw std::out_of_range(
            "op1 shape = ("+std::to_string(this->cRows)+
            ", "+std::to_string(this->cCols)+") and "+
            "op2 shape = ("+std::to_string(rhs.getRows())+
            ", "+std::to_string(rhs.getColumns())+") must be same");
    
    Matrix result = Matrix(this->cRows, this->cCols);
    for (size_t i=0; i < this->cRows; ++i) {
        for (size_t j=0; j < this->cCols; ++j) {
            result[i][j] = (*this)[i][j] + rhs[i][j];
        }
    }

    return result;
}


Matrix& Matrix::operator *= (int mult)
{
    for (size_t i=0; i < this->cRows; ++i) {
        for (size_t j=0; j < this->cCols; ++j) {
            this->rows_[i].data_[j] *= mult;
        }
    }

    return *this;
}


bool Matrix::operator == (const Matrix& rhs) const
{
    if (! (this->cRows == rhs.getRows() && this->cCols == rhs.getColumns()) )
        throw std::out_of_range(
            "op1 shape = ("+std::to_string(this->cRows)+
            ", "+std::to_string(this->cCols)+") and "+
            "op2 shape = ("+std::to_string(rhs.getRows())+
            ", "+std::to_string(rhs.getColumns())+") must be same");
    
    bool elementsEqual = true;
    for (size_t i=0; i < this->cRows; ++i) {
        for (size_t j=0; j < this->cCols; ++j) {
            if ((*this)[i][j] != rhs[i][j]) {
                elementsEqual = false;
                break;
            }
        }
    }
    return elementsEqual;
}


bool Matrix::operator != (const Matrix& rhs) const
{
    if (! (this->cRows == rhs.getRows() && this->cCols == rhs.getColumns()) )
        throw std::out_of_range(
            "op1 shape = ("+std::to_string(this->cRows)+
            ", "+std::to_string(this->cCols)+") and "+
            "op2 shape = ("+std::to_string(rhs.getRows())+
            ", "+std::to_string(rhs.getColumns())+") must be same");
    
    bool elementsEqual = true;
    for (size_t i=0; i < this->cRows; ++i) {
        for (size_t j=0; j < this->cCols; ++j) {
            if ((*this)[i][j] != rhs[i][j]) {
                elementsEqual = false;
                break;
            }
        }
    }
    return (!elementsEqual);
}


void
Matrix::show_debug()
{
    for (size_t i=0; i < this->cRows; ++i) {
        for (size_t j=0; j < this->cCols; ++j) {
            std::cout << this->rows_[i].data_[j] << "\t";
        }
        std::cout << std::endl;
    }
}


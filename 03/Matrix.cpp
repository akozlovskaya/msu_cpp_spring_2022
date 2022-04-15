#include "Matrix.hpp"

/******Vector constructor and destructor******/

Vector::Vector(size_t row_, size_t columns_num_)
    : columns_num(columns_num_), row(row_)
{
    data = new int[columns_num];
    for(size_t i = 0; i < columns_num; ++i)
        data[i] = 0;
}


Vector::~Vector()
{
    if (data != nullptr) delete []data;
}

/******Vector operator******/

int&
Vector::operator[](size_t column)
{
    if (column >= columns_num) throw std::out_of_range{""};
    return data[column];
}

/******Matrix constructor and destructor******/

Matrix::Matrix(size_t row_num_, size_t col_num_)
    : row_num(row_num_), col_num(col_num_)
{
    data = new Vector[row_num_];
    for(size_t i = 0; i < row_num_; ++i) {
        Vector tmp = Vector(i, col_num_);
        data[i] = tmp;
    }
}

Matrix::~Matrix()
{
    delete [] data;
}

/******Matrix operators******/

bool
Matrix::operator==(const Matrix &mtx) const
{
    if ((row_num != mtx.row_num) or (col_num != mtx.col_num)) return false;

    for (size_t i = 0; i < row_num; ++i)
        for (size_t j = 0; j < col_num; ++j)
            if (mtx.data[i].data[j] != data[i].data[j]) return false;
    return true;
}

bool
Matrix::operator!=(const Matrix &mtx) const
{
    return !(*this == mtx);
}

Matrix
Matrix::operator+(const Matrix &mtx) const
{
    if ((row_num != mtx.row_num) or (col_num != mtx.col_num))
        throw std::out_of_range{""};
    Matrix sum(row_num, col_num);
    for (size_t i = 0; i < row_num; ++i)
        for (size_t j = 0; j < col_num; ++j)
            sum.data[i][j] = mtx.data[i][j] + data[i][j];
    return sum;
}

Vector&
Matrix::operator[](size_t row_)
{
    if (row_ >= row_num) throw std::out_of_range{""};
    return data[row_];
}

void
Matrix::operator*=(double coef)
{
    for (size_t i = 0; i < row_num; ++i)
        for (size_t j = 0; j < col_num; ++j)
            data[i][j] *= coef;
}

/******Matrix methods******/

std::ostream& operator<<(std::ostream &out, const Matrix &mtx)
{
    out << std::endl;
    for (size_t i = 0; i < mtx.row_num; ++i) {
        for (size_t j = 0; j < mtx.col_num; ++j) {
            out << "  " << mtx.data[i][j];
        }
        out << std::endl;
    }
    return out;
}


size_t
Matrix::get_row_num() const
{
    return row_num;
}

size_t
Matrix::get_col_num() const
{
    return col_num;
}

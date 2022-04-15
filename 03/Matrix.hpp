#pragma once

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdexcept>


class Vector {
private:
    size_t columns_num;
    size_t row;
    int *data;
public:

    friend class Matrix;
    
    Vector();
    Vector(size_t, size_t);
    ~Vector();
    int& operator[](size_t);
};


class Matrix {
private:
    size_t row_num;
    size_t col_num;
    Vector *data;
public:

    Matrix(size_t, size_t);
    ~Matrix();

    size_t get_row_num() const;
    size_t get_col_num() const;

    Vector& operator[](size_t);
    void operator*=(double);
    Matrix operator+(const Matrix &) const;

    bool operator==(const Matrix&) const;
    bool operator!=(const Matrix&) const;

    friend std::ostream& operator<<(std::ostream &out, const Matrix &mtx);
};
//#ifndef MATRIX_H
//#define MATRIX_H
#pragma once

#include <iostream>
#include <vector>

namespace math
{
    #ifdef MATH_DOUBLE_PREC_DEFINE
    typedef double real;
    #else
    typedef int real;
    #endif


    class Matrix;

    class Matrix
    {
    private:
        std::vector<std::vector<real>> _matrix;

    public:
        template <typename T>
        static Matrix performMatrixOperation(const Matrix &a, const Matrix &b, T op);

        Matrix(std::vector<std::vector<real>> m) : _matrix(m) {}
        Matrix(const Matrix &m) : _matrix(m._matrix) {}
        Matrix(int rows, int cols) : _matrix(std::vector<std::vector<real>>(rows, std::vector<real>(cols))) {}

        real& operator()(int i, int j);

        Matrix &operator+=(const Matrix &other);
        Matrix &operator-=(const Matrix &other);
        Matrix &operator*=(const Matrix &other);

        friend Matrix operator+(const Matrix &a, const Matrix &b);
        friend Matrix operator-(const Matrix &a, const Matrix &b);
        friend Matrix operator*(const Matrix &a, const Matrix &b);
        friend std::ostream &operator<<(std::ostream &out, const Matrix &m);
        friend std::istream &operator>>(std::istream &in, Matrix &m);
    };

    //std::istream &operator>>(std::istream &in, Matrix &m);
}

//#endif
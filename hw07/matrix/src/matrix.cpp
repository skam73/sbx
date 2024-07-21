#include <matrix/src/matrix.h>
// #include <iostream>

using namespace math;

template <typename T>
Matrix Matrix::performMatrixOperation(const Matrix &a, const Matrix &b, T op)
{
    std::vector<std::vector<real>> result;
    for (size_t i = 0; i < a._matrix.size(); i++)
    {
        std::vector<real> row;
        for (size_t j = 0; j < a._matrix[i].size(); j++)
        {
            row.push_back(op(a._matrix[i][j], b._matrix[i][j]));
        }
        result.push_back(row);
    }
    return Matrix(result);
}

real &Matrix::operator()(int i, int j)
{
    return _matrix[i][j];
}

Matrix &Matrix::operator+=(const Matrix &other)
{
    for (size_t i = 0; i < _matrix.size(); i++)
    {
        for (size_t j = 0; j < _matrix[i].size(); j++)
        {
            _matrix[i][j] += other._matrix[i][j];
        }
    }
    return *this;
}
Matrix &Matrix::operator-=(const Matrix &other)
{
    for (size_t i = 0; i < _matrix.size(); i++)
    {
        for (size_t j = 0; j < _matrix[i].size(); j++)
        {
            _matrix[i][j] -= other._matrix[i][j];
        }
    }
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &other)
{
    for (size_t i = 0; i < _matrix.size(); i++)
    {
        for (size_t j = 0; j < _matrix[i].size(); j++)
        {
            _matrix[i][j] *= other._matrix[i][j];
        }
    }
    return *this;
}

namespace math
{

    Matrix operator+(const Matrix &a, const Matrix &b)
    {
        return Matrix::performMatrixOperation(a, b, std::plus<real>());
        /*
        std::vector<std::vector<real>> result;
        for (size_t i = 0; i < a._matrix.size(); i++)
        {
            std::vector<real> row;
            for (size_t j = 0; j < a._matrix[i].size(); j++)
            {
                row.push_back(a._matrix[i][j] +b._matrix[i][j]);
            }
            result.push_back(row);
        }
        return Matrix(result);*/
    };

    Matrix operator-(const Matrix &a, const Matrix &b)
    {
        std::vector<std::vector<real>> result;
        for (size_t i = 0; i < a._matrix.size(); i++)
        {
            std::vector<real> row;
            for (size_t j = 0; j < a._matrix[i].size(); j++)
            {
                row.push_back(a._matrix[i][j] - b._matrix[i][j]);
            }
            result.push_back(row);
        }
        return Matrix(result);
    }

    Matrix operator*(const Matrix &a, const Matrix &b)
    {
        std::vector<std::vector<real>> result;
        for (size_t i = 0; i < a._matrix.size(); i++)
        {
            std::vector<real> row;
            for (size_t j = 0; j < a._matrix[i].size(); j++)
            {
                row.push_back(a._matrix[i][j] * b._matrix[i][j]);
            }
            result.push_back(row);
        }
        return Matrix(result);
    }

    std::ostream &operator<<(std::ostream &out, const Matrix &m)
    {
        for (const auto &row : m._matrix)
        {
            for (const auto &val : row)
            {
                out << val << " ";
            }
            out << std::endl;
        }
        return out;
    }

    std::istream &operator>>(std::istream &in, Matrix &m)
    {
        for (auto &row : m._matrix)
        {
            for (auto &val : row)
            {
                in >> val;
            }
        }
        return in;
    }
}
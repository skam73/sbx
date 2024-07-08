#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

namespace hw
{
    class Matrix
    {
    private:
        std::vector<std::vector<int>> _matrix;

        template <typename BinaryOperation>
        static Matrix performMatrixOperation(const Matrix &a, const Matrix &b, BinaryOperation op)
        {
            std::vector<std::vector<int>> result;
            for (size_t i = 0; i < a._matrix.size(); i++)
            {
                std::vector<int> row;
                for (size_t j = 0; j < a._matrix[i].size(); j++)
                {
                    row.push_back(op(a._matrix[i][j], b._matrix[i][j]));
                }
                result.push_back(row);
            }
            return Matrix(result);
        }

    public:
        Matrix(std::vector<std::vector<int>> m) : _matrix(m) {}
        Matrix(Matrix &m) : _matrix(m._matrix) {}
        Matrix(int rows, int cols) : _matrix(std::vector<std::vector<int>>(rows, std::vector<int>(cols))) {}

        int &operator()(int i, int j)
        {
            return _matrix[i][j];
        }

        friend Matrix operator+(const Matrix &a, const Matrix &b)
        {
            return performMatrixOperation(a, b, std::plus<int>());
        }

        friend Matrix operator-(const Matrix &a, const Matrix &b)
        {
            return performMatrixOperation(a, b, std::minus<int>());
        }

        friend Matrix operator*(const Matrix &a, const Matrix &b)
        {
            return performMatrixOperation(a, b, std::multiplies<int>());
        }

        friend std::ostream &operator<<(std::ostream &out, const Matrix &m)
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

        friend std::istream &operator>>(std::istream &in, Matrix &m)
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

        Matrix &operator+=(const Matrix &other)
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
        Matrix &operator-=(const Matrix &other)
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
        Matrix &operator*=(const Matrix &other)
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
    };
}

using namespace hw;

int main()
{
    try
    {

        Matrix m1({{1, 2}, {3, 4}});
        Matrix m2({{5, 6}, {7, 8}});

        m1(0, 0) = 0;

        // std::cin >> m1;

        Matrix addition = m1 + m2;

        m1 += m2;

        std::cout << addition << std::endl;

        std::cout << m1 << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
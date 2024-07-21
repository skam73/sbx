#include "matrix/src/c/c_api.h"
#include "matrix/src/matrix.h"

#include <iostream> // Include the iostream header

struct Matrix : public math::Matrix
{
    Matrix(const struct math::Matrix &m) : math::Matrix(m) {};
};

Matrix *MATRIXLIB_EXPORT math_createMatrix(int rows, int cols)
{
    return new Matrix(math::Matrix(rows, cols));
}

void MATRIXLIB_EXPORT math_deleteMatrix(Matrix *m)
{
    delete m;
}

real MATRIXLIB_EXPORT math_get(Matrix *m, int row, int col)
{
    return m->operator()(row, col);
}

void MATRIXLIB_EXPORT math_set(Matrix *m, int row, int col, real val)
{
    m->operator()(row, col) = val;
}

Matrix *MATRIXLIB_EXPORT math_add(const Matrix *a, const Matrix *b)
{
    return new Matrix(*a + *b);
}

Matrix *MATRIXLIB_EXPORT math_subtract(const Matrix *a, const Matrix *b)
{
    return new Matrix(*a - *b);
}

Matrix *MATRIXLIB_EXPORT math_dot(const Matrix *a, const Matrix *b)
{
    return new Matrix(*a * *b);
}

void MATRIXLIB_EXPORT math_print(const Matrix *m)
{
    std::cout << *m << std::endl;
}
#pragma once

#include <src/export.h>

//
#ifdef MATH_DOUBLE_PREC_DEFINE
typedef double real;
#else
typedef int real;
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct Matrix Matrix;

    Matrix *MATRIXLIB_EXPORT math_createMatrix(int rows, int cols);

    void MATRIXLIB_EXPORT math_deleteMatrix(Matrix *m);

    real MATRIXLIB_EXPORT math_get(Matrix *m, int row, int col);

    void MATRIXLIB_EXPORT math_set(Matrix *m, int row, int col, real val);

    Matrix *MATRIXLIB_EXPORT math_add(const Matrix *a, const Matrix *b);

    Matrix *MATRIXLIB_EXPORT math_subtract(const Matrix *a, const Matrix *b);

    Matrix *MATRIXLIB_EXPORT math_dot(const Matrix *a, const Matrix *b);

    void MATRIXLIB_EXPORT math_print(const Matrix *m);

#ifdef __cplusplus
}
#endif
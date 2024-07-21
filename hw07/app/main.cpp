#include <iostream>
using namespace std;

struct Matrix;
typedef double real;

#ifdef __cplusplus
extern "C"
{
#endif

Matrix* math_createMatrix(int rows, int cols);

void math_deleteMatrix(Matrix* m);

real math_get(Matrix* m, int row, int col);

void math_set(Matrix* m, int row, int col, real val);

Matrix* math_add(const Matrix* a, const Matrix* b);

Matrix* math_subtract(const Matrix* a, const Matrix* b);

void math_print(const Matrix* m);

#ifdef __cplusplus
}
#endif

//

int main(){

    Matrix* a = math_createMatrix(3,3);
    Matrix* b = math_createMatrix(3,3);

    math_set(a, 0, 0, 1.0);
    math_set(b, 0, 0, 2.0);

    Matrix* c = math_add(a,b);
    math_print(c);

    math_deleteMatrix(a);
    math_deleteMatrix(b);
    math_deleteMatrix(c);
    
    return 0;
}
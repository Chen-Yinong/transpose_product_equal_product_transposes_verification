#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

typedef struct 
{
    size_t rows;
    size_t cols;
    double* data;
}Matrix;
Matrix mat_create(size_t rows,size_t cols);
void mat_check(Matrix* A);
void mat_free(Matrix* A);

double mat_get(const Matrix* A,size_t r,size_t c);
void mat_set(Matrix* A,size_t r,size_t c,double v);

void mat_print(const Matrix* A,const char *name);
Matrix mat_transpose(const Matrix* A);
Matrix mat_mul(const Matrix* A,const Matrix* B);
int mat_equal(const Matrix* A,const Matrix* B);
int mat_verification(const Matrix* A,const Matrix* B);

#endif

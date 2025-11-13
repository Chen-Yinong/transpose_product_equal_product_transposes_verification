#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

Matrix mat_create(size_t rows,size_t cols)
{
    Matrix A={rows,cols,NULL};
    A.data = (double*)calloc(rows*cols,sizeof(double));
    return A;
}

void mat_check(Matrix* A)
{
    if (A->data == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(0);
    }
}

void mat_free(Matrix* A)
{
    free(A->data);
    A->data = NULL;
    A->rows = 0;
    A->cols = 0;
}

double mat_get(const Matrix* A,size_t r,size_t c)
{
    return A->data[r*A->cols+c];
}

void mat_set(Matrix* A,size_t r,size_t c,double v)
{
    A->data[r*A->cols+c]=v;
}

void mat_print(const Matrix* A,const char *name)
{
    if (name)
    {  
        printf("%s=\n",name);
    }
    for (size_t i = 0; i < A->rows; i++)
    {
        for (size_t j = 0; j < A->cols; j++)
        {
            printf("%.3f ",mat_get(A,i,j));
        }
        printf("\n");
    }
}

Matrix mat_transpose(const Matrix* A)
{
    Matrix AT=mat_create(A->cols,A->rows);
    for (size_t i = 0; i < A->rows; i++)
    {
        for (size_t j = 0; j < A->cols; j++)
        {
            mat_set(&AT,j,i,mat_get(A,i,j));
        }
    }
    return AT;
}

Matrix mat_mul(const Matrix* A,const Matrix* B)
{
    Matrix product=mat_create(A->rows,B->cols);
    double sum=0;
    for (size_t i = 0; i < product.rows; i++)
    {
        for (size_t j = 0; j < product.cols; j++)
        {
            sum=0;
            for (size_t k = 0; k < A->cols; k++)
            {
                sum+=mat_get(A,i,k)*mat_get(B,k,j);
            }
            mat_set(&product,i,j,sum);
        }
    }
    return product;
}

int mat_equal(const Matrix* A,const Matrix* B)
{
    if (A->rows != B->rows || A->cols != B->cols)
    {
        return 0;
    }
    for (size_t i = 0; i < A->rows; i++)
    {
        for (size_t j = 0; j < A->cols; j++)
        {
            if (mat_get(A,i,j)-mat_get(B,i,j) > 1e-9)
            {
                return 0;
            }
            
        }
    }
    return 1;
}//0表示不相等，1表示相等

int mat_verification(const Matrix* A,const Matrix* B)
{
    Matrix AB=mat_mul(A,B);
    Matrix ABT=mat_transpose(&AB);
    mat_print(&AB,"AB");
    Matrix AT=mat_transpose(A),BT=mat_transpose(B);
    Matrix BTAT=mat_mul(&BT,&AT);
    mat_print(&BTAT,"BTAT");
    int r=mat_equal(&ABT,&BTAT);
    mat_free(&AB);
    mat_free(&ABT);
    mat_free(&AT);
    mat_free(&BT);
    mat_free(&BTAT);
    return r;
}

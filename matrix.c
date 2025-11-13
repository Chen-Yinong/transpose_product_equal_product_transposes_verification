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
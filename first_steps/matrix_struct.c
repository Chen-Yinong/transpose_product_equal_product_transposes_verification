#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include<time.h>

const size_t R = 2;
const size_t C = 3;

typedef struct 
{
    size_t rows;
    size_t cols;
    double *data;
}Matrix;

Matrix mat_create(size_t rows,size_t cols)
{
    Matrix A;
    A.rows = rows;
    A.cols = cols;
    A.data = (double*)calloc(rows*cols,sizeof(double));
    if (A.data == NULL) 
    {
    printf("内存申请失败！\n");
    exit(1);//退出程序
    }
    return A;
}

void mat_free(Matrix *A)
{
    free(A->data);
    A->data = NULL;
    A->cols = A->rows = 0;
}

static inline double mat_get(const Matrix *A,size_t r,size_t c)
{
    return A->data[r*A->cols + c];
}

static inline void mat_set(Matrix *A,size_t r,size_t c,double v)
{
    A->data[r*A->cols + c] = v;
}

void mat_print(const Matrix *A,const char *name)
{
    if (name)
    {
        printf("%s = \n",name);        
    }
    for (size_t i = 0; i < A->rows; i++)
    {
        for (size_t j = 0; j < A->cols; j++)
        {
           printf("%8.3f ",mat_get(A,i,j));
        }
        printf("\n");
    }
}

int main(void)
{
    Matrix my_1st_mat=mat_create(R,C);
    srand((unsigned)time(NULL));
    for (size_t i = 0; i < R; i++)
    {
        for (size_t j = 0; j < C; j++)
        {
            mat_set(&my_1st_mat,i,j,rand()%10);
        }
        
    }
    
    mat_print(&my_1st_mat,"my_1st_mat");
    mat_free(&my_1st_mat);
    return 0;
    
}
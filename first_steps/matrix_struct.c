//mostly copied from AI
#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

const size_t R = 2;
const size_t C = 3;

/*const size_t R1=2;
const size_t C1=3;
const size_t R2=3;
const size_t C2=2;*/

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
    return A;
}

void mat_check(Matrix *A)
{
    if (A->data == NULL) 
    {
    printf("Memory allocation failed!\n");
    exit(1);//退出程序
    }
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

Matrix mat_transpose(const Matrix *A)
{
    Matrix AT=mat_create(A->cols,A->rows); 
    mat_check(&AT);
    for (size_t i = 0; i < A->rows; i++)
    {
        for (size_t j = 0; j < A->cols; j++)
        {
            mat_set(&AT,j,i,mat_get(A,i,j));
        }
        
    }
    return AT;
}

Matrix mat_mul(const Matrix *A,const Matrix *B)
{
    if (A->cols != B->rows)
    {
        printf("These two matrices cannot be multiplied\n");
        return (Matrix){0,0,NULL};
    }
    Matrix product = mat_create(A->rows,B->cols);
    mat_check(&product);
    for (size_t i = 0; i < A->rows; i++)
    {
        for (size_t j = 0; j < B->cols; j++)
        {
            double sum=0;
            for (size_t k = 0; k < A->cols; k++)
            {
                sum +=mat_get(A,i,k)*mat_get(B,k,j);
            }
            mat_set(&product,i,j,sum);
        }
    }
    return product;
}
int mat_equal(const Matrix *A,const Matrix *B)
{
    if (A->rows != B->rows || A->cols!=B->cols)
    {
        return 0;
    }
    for (size_t i = 0; i < A->rows; i++)
    {
        for (size_t j = 0; j < A->cols; j++)
        {
            if (fabs(mat_get(A,i,j)-mat_get(B,i,j))>1e-9)
            { 
                return 0;
            }
        }
        
    }
    return 1;
}
int mat_verification(const Matrix *A,const Matrix *B)
{
    Matrix m1=mat_mul(A,B);//先乘再转
    Matrix m2=mat_transpose(&m1);
    Matrix m3=mat_transpose(A),m4=mat_transpose(B);//先转再乘
    Matrix m5=mat_mul(&m4,&m3);
    
    int result=mat_equal(&m2,&m5);

    mat_free(&m1);
    mat_free(&m2);
    mat_free(&m3);
    mat_free(&m4);
    mat_free(&m5);
    return result;
}

int main(void)
{

    Matrix my_1st_mat=mat_create(R,C);
    mat_check(&my_1st_mat);
    srand((unsigned)time(NULL));
    for (size_t i = 0; i < R; i++)
    {
        for (size_t j = 0; j < C; j++)
        {
            mat_set(&my_1st_mat,i,j,rand()%10);
        }
        
    }
    
    mat_print(&my_1st_mat,"my_1st_mat");

    Matrix my_2nd_mat=mat_create(C,R);
    mat_check(&my_2nd_mat);
    srand((unsigned)time(NULL));
    for (size_t i = 0; i < R; i++)
    {
        for (size_t j = 0; j < C; j++)
        {
            mat_set(&my_2nd_mat,i,j,rand()%10);
        }
        
    }
    printf("%d",mat_verification(&my_1st_mat,&my_2nd_mat));
    //mat_print(&my_2nd_mat,"my_2nd_mat");
    //Matrix m=mat_mul(&my_1st_mat,&my_2nd_mat);
    //mat_print(&m,"Product");
    //缺free
    return 0;


    /*Matrix my_1st_mat=mat_create(R,C);
    mat_check(&my_1st_mat);
    srand((unsigned)time(NULL));
    for (size_t i = 0; i < R; i++)
    {
        for (size_t j = 0; j < C; j++)
        {
            mat_set(&my_1st_mat,i,j,rand()%10);
        }
        
    }
    
    mat_print(&my_1st_mat,"my_1st_mat");
    Matrix my_2nd_mat=mat_transpose(&my_1st_mat);
    mat_print(&my_2nd_mat,"my_2nd_mat");
    mat_free(&my_1st_mat);
    mat_free(&my_2nd_mat);*/   
}
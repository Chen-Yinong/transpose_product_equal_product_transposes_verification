#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"matrix.h"

#define R 2
#define C 3

int main()
{
    srand((unsigned)(time(NULL)%10));
    Matrix A1=mat_create(R,C),A2=mat_create(C,R);
    mat_check(&A1);
    mat_check(&A2);
    for (size_t i = 0; i < A1.rows; i++)
    {
        for (size_t j = 0; j < A1.cols; j++)
        {
            mat_set(&A1,i,j,rand()%10);
        }
        
    }
    for (size_t i = 0; i < A2.rows; i++)
    {
        for (size_t j = 0; j < A2.cols; j++)
        {
            mat_set(&A2,i,j,rand()%10);
        }
        
    }
    
    mat_print(&A1,"1st matrix");
    mat_print(&A2,"2nd matrix");
    
    printf("\n%d\n\n",mat_verification(&A1,&A2));
    printf("Please enter to exit ...");
    getchar();//否则窗口一闪就没！
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

int main(int argc , char ** argv)
{
    int i = 0;
    struct vector * p  = NULL;
    int a[50] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,1111,16,17,18,19,20,21,22,23,24,25,26,27};
    
    for(i = 0 ; i < 50 ; i++)
    {
        VEC_ADD(p , &a[i]);
    }
    
    for(i = 0 ; i < 50 ; i++)
    {
        printf("%d\n",*((int *)p->head[i]));
    }
    
    
    printf("p->length = %d\n" , p->length );
    
    printf("%d\n" , *((int *)VEC_GET(p,15)));
    
    VEC_FREE(p);

}
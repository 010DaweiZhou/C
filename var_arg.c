#include <stdio.h>
#include <stdarg.h>

#define PRINT(format,...) printf("%s[%d]%s:"format,__FILE__,__LINE__,__FUNCTION__,##__VA_ARGS__);

static int
average(int num , ...)
{
    va_list v ;
    int count = 0;
    int sum   = 0;
    
    va_start(v,num);
    
    for(; count < num; count++)
    {
        sum += va_arg(v,int);
    }
    
    va_end(v);
    
    return sum;
}

int main(int argc ,char ** argv)
{
    
    PRINT("%d\n",average(4,1,2,3,4));
    PRINT();
    return 0;
}
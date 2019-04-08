#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	"  "
	find .h from current dirctionary first, 
	find from path if is not found
*/
#include "9.h"

int main()
{
	// with symbol
	int a = -10;
	int b = a>>3;
	printf("%d\n",b);
	
/* #error hello,i am error	 */
	domain x ;
	x.a = 1;
	x.b = 2;
	x.c = 3;
	
	printf("%s %d %d\n",__FILE__, __LINE__, x.a);
	printf("%d\n",x.b);
	printf("%d\n",x.c);
	
	
#ifdef MAX
	printf("%d\n",MAX(100,200));	
#else
	printf("%d\n",ADD(100,200));
#endif	
	
	
#if 1 
	printf("%d\n",MAX(100,200));
#else
	printf("%d\n",ADD(100,200));
#endif


	return 0;
	
}
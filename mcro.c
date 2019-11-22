#include <stdio.h>
#include <stdlib.h>

#define PF(x) printf(" N " #x " B \n");

#define XNAME(n) x##n

#define PR(...) printf(__VA_ARGS__)

#define RANDOM (-1.0 + 2.0*(double)rand()/RAND_MAX)

#define _(type)							    \
	static __inline type x_##type(type x)	\
	{									    \
		return x + x ;				        \
	}

#define SUM(a,b) \
do{\
	int d = 0;\
	d = a+b;\
	printf("a = %d\n",a);\
	printf("b = %d\n",b);\
	printf("a+b = %d\n",d);\
}while(0)
	
_(int);
_(char);


int main()
{
	int XNAME(1) = 12;
	printf("XNAME(n) = %d\n",x1);
	PR("hello world! %d\n" , 100);
	PF(9);
	
	PR("%f\n" , RANDOM);
	
	int y = x_int(10);
	printf("%d\n",y);

	SUM(1,2);
	printf("%d")

	exit(0);
}
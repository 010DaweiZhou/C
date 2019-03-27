#include <stdio.h>
#include "generic.h"
#include <string.h>
#include <limits.h>

int fun1(int a ,int b )
{
/* 	sum是局部变量，动态变量，
	运行时分配内存,手动初始化 */
	int sum = 0;
	return sum;
}
int fun2()
{
/* 	函数结束之后仍然保留,存储在静态存储区，
	编译时赋值，并且只赋值一次，
	整个程序运行期间都不释放 */
	static int sum = 0;
	sum++;
	printf("%d\n",sum);
}

int fun3()
{
	register int i ,f = 1;
	for(i = 1; i < 100; i++)
	{
		f *= i;
	}
	return f;
}

int main()
{
/* 	char name[40] = "hello world!";
	
	printf("%s\n",name);
	
	printf("%lu\n",strlen(name));
	
	printf("%lu\n",sizeof(name)); */
	
	
/* 	float area = 0 , circum = 0 , radius = 0;
	
	printf("What is the radius of your roundness?\n");
	
	scanf("%f",&radius);
	
	area = PI * radius * radius;
	
	circum = 2 * PI * radius;
	
	printf("area is %.2f , circum is %.2f\n",area,circum); */
	
	printf("UINT_MAX is :%u\n",UINT_MAX);
	
	printf("INT_MAX is :%d\n",INT_MAX);
	
	printf("INT_MIN is :%d\n",INT_MIN);
	
	printf("%d\n",PAGES);
	printf("%2d\n",PAGES);
	printf("%10d\n",PAGES);
	
	
	
/* 	int x=0,y=0,a=2,b=4;
	//先分别计算两个表达式的值(从左到右)，表达式2的值作为表达式的值给y
	y=((x=a-b),(x+b));
	printf("x=%d,y=%d\n",x,y);
	
	switch(y)
	{
		case 1:
			printf("hello world???\n");
		case 2:
			printf("hello world!!!\n");
		default:
			break;
	} */
	
	//n!
	int n = 0;
	long s = 1;
	int i = 1;
	
	printf("input n:");
	scanf("%d",&n);
	//*读取但是不会赋值 
	//scanf("%*d",&n)；编不过
	scanf("%*d");
	
	if(n <= 0)
		return -1;
	
	while(i <= n)
	{
		s *= i;
		i++;
	}
	
	printf("%ld\n",s);
	
	
	putchar('a');
	putchar('\n');
	
	//声明外部变量
	extern int ww,cc;
	printf("%d,%d\n",ww,cc);
	
	for(int i = 0 ; i < 10 ; i ++)
	{
		fun2();
	}

	int a[3][5] = { {1,2,3,4,5},
					{2,3,4,5,6},
					{3,4,5,6,7}	};
	
	for(int row = 0;row < 3;row ++)
	{
		for (int column = 0 ; column < 5 ; column ++)
		{
			printf("%d ",a[row][column]);
		}
		printf("\n");
	}
	
	char china[] = "china";
	printf("%s\n",china);
	
	return 0;
}

int ww = 10;
int cc = 20;
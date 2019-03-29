#include <stdio.h>
#include <string.h>
#include "5.h"

double fun()
{
	printf("i'm in fun...\n");
	return 0;
}

int main()
{
	char * str = "hello world!";
	char string[] = "hello world!";
	char * p = str;
	
	
	printf("%s\n",str);
	printf("%s\n",string);
	
/* 	尝试修改字符串常量，挂
	*str = "Tim apple"; */
	
/* 	修改指针的方向，没问题 */
	str = "Tim apple";
	printf("%s\n",str);
	
/* 	p不受影响 */
	printf("%s\n",p);
	
/* 	数组内容可以正常修改 */
	string[0] = 'x';
	printf("%s\n",string);
	
/*	声明函数指针并赋值*/
	double (* p_fun) () = fun;
	
/* 	调用函数指针 */
	(* p_fun)();
	
	printf("student's size = %zd\n",sizeof(struct student));
	
	struct student sam ;
	struct student students[10];
	memset(&sam,0,sizeof(struct student));
	
	sam.name = "sam";
	sam.age = 10;
	sam.address = "Beijing";
	printf("name = %s \n",(sam.name));
	
	
	printf("sam's name's p =  %p \n", sam.name);
	printf("sam's p = %p \n", &(sam));
	
	u32_t a = 0;
	printf("%d\n",&a);
	
	return 0;
}
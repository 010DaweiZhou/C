#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student{
	char name[10];
	void * (* action)(void);
};

void getmemory1(char ** p ,int number)
{
	*p = (char *) malloc(number);
	
}

void getmemory2(char * p ,int number)
{
	p = (char *) malloc(number);
	
}

/*
//warning :return a local variable point
char * getmemory3(void)
{
	char p[] = "hello world";
	return p;
}
*/

char * mystrcpy(char *dest , char *source)
{
	if(dest == NULL || source == NULL)
		return NULL;
	
	if(dest == source)
		return dest;
		
	char * strdest = dest ;
	
	while( (*dest++ = *source++) != '\0');
	return strdest;
}

void * myprintf(void)
{
	printf("%s","hello!\n");
}

int main(int argc , char ** argv)
{
#if 0
	char * str = NULL;
	getmemory1(&str,100);
	//getmemory2(str,100);
	strcpy(str,"hello");
	printf("%s",str);
	exit(0);
	
#endif
#if 0
	char* str = (char *)malloc(100);
	strcpy(str,"hello");
	free(str);
	if(str!=NULL)
	{
		strcpy(str,"world");
		printf("%s",str);
	}
	exit(0);
#endif
#if 0	
	char * str = NULL;
	str = getmemory3();
	printf("%p %s",str,str);
#endif	
#if 0	
	int a = 1;
	
	switch(a)
	{
		case 1:
		{
			printf("hello !\n");
			break;
		}
		case 2:
		case 3:
		{
			printf("world !\n");
			break;
		}
		default:
		{
			printf("bye !\n");
			break;
		}	
	}

	exit(0);
	#endif
#if 0
	char a[100] = {0};
	char *b = "hello world!";
	
	mystrcpy(a,b);
	
	printf("%s",a);
#endif
#if 0
	struct student a = {0};
	strcpy(a.name , "sam");
	a.action = myprintf;
	a.action();
	printf("%p\n",a.action);
#endif

}


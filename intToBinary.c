#include <stdio.h>
#include <stdlib.h>

int main(int argc , char ** argv)
{
	int a = 0;
	
	if(argc != 2)
		return -1;
	
	a = atoi(argv[1]);
	if(!a)
		return -1;
	
	printf("%d\n",a);
	
	int i = 0;
	int l = sizeof(a) * 8;
	
	/* ignore the highest bit */
	for ( i = l-1 ; i >= 0 ; i--)
	{
		if(a &(1<<i))
			break;
	}
	
	for ( ; i >= 0 ; i--)
	{
		printf("%d" , (a&(1<<i)) != 0 );
	}
	
	printf("\n");
	return 0;
}
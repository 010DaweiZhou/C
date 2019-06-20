#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) sizeof(a)/sizeof(a[0])
#define X(a) (a++)*(a++) 


void bubbling_fun(int a[] , int length)
{
	int i = 0 ;
	int j = 0 ;
	int temp = 0;
	
	for( i = 0; i < length ; i ++)
	{
		for ( j = i + 1; j < length ; j ++)
		{
			if(a[i] > a[j])
			{
				a[i] ^= a[j];
				a[j] ^= a[i];
				a[i] ^= a[j];
			}
		}
	}
}

int main(int argc , char ** argv)
{
	int i = 0;
	int a[] = {99,98,97,96,95,94,93,92,91,90};
	
	for (i = 0; i < LENGTH(a) ; i++)	
	{
		i < LENGTH(a) -1 ? printf("%d.",a[i]) : printf("%d\n",a[i]);
	}
	
	bubbling_fun(a , LENGTH(a));
	
	for (i = 0 ; i < LENGTH(a) ; i++)	
	{
		i < LENGTH(a) -1 ? printf("%d.",a[i]) : printf("%d\n",a[i]);
	}
	
	int x = 10;
	/* 10 * 11 */
	printf("X = %d , x = %d\n",X(x),x);
	
	exit(0);
}
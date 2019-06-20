#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) sizeof(a)/sizeof(a[0])

void sort_fun(int a[] , int low , int high)
{
	int i = low ; 
	int j = high;
	int key = a[i];
	
	if(i > j)
		return;
	
	while(i < j)
	{
		while((a[j] >= key) && ( i < j))
		{
			j--;
		}
		a[i] = a[j];
		
		while((a[i] <= key) && (i < j))
		{
			i++;
		}
		a[j] = a[i];
		
	}
	
	a[i] = key;
	sort_fun(a, low  , i-1);
	sort_fun(a, j + 1, high);
		
}


int main(int argc , char ** argv)
{
	int i = 0;
	int a[] = {99,98,97,96,95,94,93,92,91,90};
	
	
	for (i = 0; i < LENGTH(a) ; i++)	
	{
		i < LENGTH(a) -1 ? printf("%d.",a[i]) : printf("%d\n",a[i]);
	}
	
	sort_fun(a , 0 , LENGTH(a)-1 );
	
	for (i = 0 ; i < LENGTH(a) ; i++)	
	{
		i < LENGTH(a) -1 ? printf("%d.",a[i]) : printf("%d\n",a[i]);
	}
	
	exit(0);
}
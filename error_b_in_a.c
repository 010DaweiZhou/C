#include <stdio.h>

struct a 
{
	struct b * bb;
	int x;
	int z;
};

struct b
{
	int y ;
};


int main()
{
	struct a aa = 
	{
		.z = 1,
		.x = 2
	};
	
	/* b is NULL , Segmentation fault here */
	printf("a->b->y = %d" , aa.bb->y);
	
	return 0;
}
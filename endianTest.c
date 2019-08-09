#include <stdio.h>
#include <stdlib.h>

union test{
	unsigned short a ; 
	unsigned char i[2];
};


int main()
{
	union test u ;
	u.i[0] = 0x12;
	u.i[1] = 0x34;
	
	
	/* 
		0x1234 big , 0x3412 little
	*/
	printf("0x%x\n",u.a);
	exit(0);
}
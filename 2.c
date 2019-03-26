#include <stdio.h>
#include "2.h"

int main(int argc , char** argv){
	
	int result = 0;
	
	if(argc < 2)
	{
		printf("please input one param at least!\n");
		return 0;
	}
	
	for(int i = 0 ; i < argc ; i++){
		printf("argc[%d] = %s\n",i,argv[i]);
	}
	
	result = area(100,100);
	printf("area = %d \n" , result);
	return 0;
}


int area(int length , int width)
{
	return length * width;
}
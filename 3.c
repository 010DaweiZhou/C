#include <stdio.h>
#include "generic.h"
#include <stdint.h>
#include <inttypes.h>

int main()
{
/* 	float weight = 0;
	printf("input float: ");
	scanf("%f",&weight);
	printf("the value you input: %f\n",weight); */
	
	
	//64 bits
	printf("long:%ld\n",sizeof(long));
	
	//64 bits
	printf("long long:%ld\n",sizeof(long long));
	
	//16 bits
	printf("short:%ld\n",sizeof(short));
	
	//32 bits
	printf("int:%ld\n",sizeof(int));
	
	//32 bits
	printf("float:%ld\n",sizeof(float));
	
	
	//64 bits
	printf("double:%ld\n",sizeof(double));
	
	//64 bits computer , int * 64 bits
	printf("int *:%ld\n",sizeof(int *));
	
	//32 bits wherever
	printf("int32_t : %ld\n",sizeof(int32_t));
	
	//128 bits
	printf("long double : %ld\n",sizeof(long double));
	
	//octonary number
	u_32t a = 010;
	printf("%d\n",a);
	printf("%x\n",a);
	printf("%o\n",a);
	
	//with prefix 
	printf("%d\n",a);
	printf("%#x\n",a);
	printf("%#o\n",a);
	
	int32_t me32;
	printf("me32 = %" PRId32 "\n",me32);
	
/* 	u_8t my_char ;
	printf("please input a char:");
	scanf("%c",&my_char);
	printf("you input :%c ,%d\n",my_char,my_char); */
	
	float w = 0xa.1fp10;
	printf("%f\n",w);
	printf("%e\n",w);
	
	float aboat = 32000.0;
/* 	double abet = 2.14e9;
	long double dip = 5.32e-5; */
	printf("%a in hexadecimal \n",aboat);
	
	
	float g,h;
	float tax , rate;
	g = 0x0.1p20;
	tax = g * rate;
	printf("%f\n",g);

	
	return 0;
}


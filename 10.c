#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "10.h"

long calculate(int a , int b )
{
	return a*a + b*b;
}

int main(int argc , void * argv[] )
{
	// int a = 0;
	// int b = 0;
	// long result = 0;
	
	// while(1)
	// {
		// printf("input value :");
		// scanf("%d %d",&a,&b);
		// if(a == 0 && b ==0 )
			// exit(0);
		
		// result = calculate(a,b);
		// printf("the result = %ld\n",result);
	// }
	
	char buf[64] ;
	struct ipv6_addr ipv6_add;
	
	memset(buf, 0 ,64);

	char addr[16] = {0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
					0x64, 0x1e, 0x81, 0xff, 0xfe, 0x1, 0x2, 0x4};
	
	memcpy(ipv6_add.ipv6 , addr , 16);
	
	/*whether with (uint16_t) or not are ok*/
	sprintf(buf, "%X:%X:%X:%X:%X:%X:%X:%X",  ((uint16_t)ipv6_add.ipv6[0] << 8) + ipv6_add.ipv6[1],
											 ((uint16_t)ipv6_add.ipv6[2] << 8) + ipv6_add.ipv6[3],
											 ((uint16_t)ipv6_add.ipv6[4] << 8) + ipv6_add.ipv6[5],
											 ((uint16_t)ipv6_add.ipv6[6] << 8) + ipv6_add.ipv6[7],
											 ((uint16_t)ipv6_add.ipv6[8] << 8) + ipv6_add.ipv6[9],
											 ((uint16_t)ipv6_add.ipv6[10] << 8) + ipv6_add.ipv6[11],
											 ((uint16_t)ipv6_add.ipv6[12] << 8) + ipv6_add.ipv6[13],
											 ((uint16_t)ipv6_add.ipv6[14] << 8) + ipv6_add.ipv6[15]);
	
	sprintf(buf, "%X:%X:%X:%X:%X:%X:%X:%X",  (uint16_t)ipv6_add.ipv6[0] * 256 + ipv6_add.ipv6[1],
											 (uint16_t)ipv6_add.ipv6[2] * 256 + ipv6_add.ipv6[3],
											 (uint16_t)ipv6_add.ipv6[4] * 256 + ipv6_add.ipv6[5],
											 (uint16_t)ipv6_add.ipv6[6] * 256 + ipv6_add.ipv6[7],
											 (uint16_t)ipv6_add.ipv6[8] * 256 + ipv6_add.ipv6[9],
											 (uint16_t)ipv6_add.ipv6[10] * 256 + ipv6_add.ipv6[11],
											 (uint16_t)ipv6_add.ipv6[12] * 256 + ipv6_add.ipv6[13],
											 (uint16_t)ipv6_add.ipv6[14] * 256 + ipv6_add.ipv6[15]);
												 
	
/* 	char * a = "hello world::china";
	char * b = strstr("hello world::china","::");
	int offset = (int)(b-a);
	printf("%d\n",offset);
	memcpy(buf ,a ,b-a);
	printf("%s\n",buf);
	
	buf[offset++] = ':';
	buf[offset++] = ':';
	printf("%s\n",buf);
	
	char mac[6] = {'a','b','c','d','e','f'};
	int flag = 0;
	for(int i = 0; i < 6 ; i ++)
	{
		memcpy(buf+offset , &mac[i] , sizeof(char));
		offset += sizeof(char);
		flag++;
		if(flag == 2 && i != 5)
		{
			buf[offset++] = ':';
			flag = 0;
		}	
	}
	printf("%s\n",buf); */
	
	
/* 	char * str = "ffff::1";
	
	int length = strlen(str);
	char x[6] = {0xa0,0xff,0xff,0xff,0xff,0xff} ;
	int i = 0;
	
	for (length; length > 0 ; length--)
	{
		if(!memcmp(str,"::",2))
		{
			memcpy(&buf[i++],"::",2);
			break;
		}	
		memcpy(&buf[i++],str,1);
		str++;
	} */
	

/* 	memcpy(&buf[i++],&x,3);
	buf[i++] = 0xff;
	buf[i++] = 0xfe;
	memcpy(&buf[i++],&x[3],3); */


	printf("%s",buf);
	printf("\n");
	

	return 0;
}
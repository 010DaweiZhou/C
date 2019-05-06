#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*******************************
	generate x*y static route 
*******************************/
int main(int argc , char * argv[])
{
	if(argc < 3 )
	{
		printf("Two param (x * y) needed !\n");
		exit(1);
	}
	
	char filename[1024];
	memset(filename, 0 , 1024);
	printf("Please input the output filename: ");
	scanf("%s",filename);
	printf("\n");
	
	
	int x = atoi(argv[1]);
	if(x > 255)
	{
		printf("Too large number , x change to 255\n\n");
		x = 255;
	}
		
	int y = atoi(argv[2]);
	if(y > 255)
	{
		printf("Too large number , y change to 255\n\n");
		y = 255;
	}
	
	printf("%d * %d static route will be generated!\n\n", x, y);
	sleep(1);

	
	FILE * file = fopen(filename,"w");
	if(!file)
	{
		printf("open file failed!\n");
		exit(1);
	}
	
	int ret = 0;
	for(int i = 0 ; i < x ; i++)
	{
		for (int j = 0 ; j < y ; j++)
		{
			ret = fprintf(file,"  ip route 100.%d.%d.1/24 blackhole\n",i,j);
			if( -1 == ret)
			{
				printf("Error occurred! exit!\n");
				fclose(file);
				exit(-1);
			}
		}
	}
	
	printf("write %d static-route to %s successful!\n\n", x*y, filename);
	fclose(file);	
	
	return 0;
}
#include <stdio.h>
#include <string.h>
#include "generic.h"

int main(int argc , char * argv[])
{
	
	if(argv[1] == NULL)
	{
		return -1;
	}
	
	FILE * file = fopen(argv[1],"w");
	if(!file)
		return -1;
	
	/* format IO*/
	if(fprintf(file,"hello world!\n") < 0 )
		return -1;
	
	printf("format write successful!\n\n");
	fclose(file);
	file = NULL;
	
	char buf[BUF_SIZE];
	memset(buf , 0 , BUF_SIZE);
	sprintf(buf,"%s","hello world!");
	printf("%s\n",buf);
	
	
	memset(buf , 0 , BUF_SIZE);
	printf("input:");
	scanf("%s",buf);
	printf("%s\n",buf);
	
	
	/* reading will stop when space /t /n existed*/
	memset(buf, 0 , BUF_SIZE);
	file = fopen(argv[1],"r");
	if(!file)
		return -1;
	fscanf(file,"%s",buf);
	printf("%s\n", buf);
	fclose(file);
	
	
	/* reading will stop when space /t /n existed */
	memset(buf , 0 ,BUF_SIZE);
	char * str = "hello world";
	sscanf(str , "%s" , buf);
	printf("%s\n",buf);
	
	return 0 ;
}
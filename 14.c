#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 512


int main(int argc , char * argv[])
{
	char buf[SIZE] = {};
	
	if(argc != 2 || strlen(argv[1]) == 0)
	{
		printf("please input a path!\n");
		exit(1);
	}
	
	/*go to specified path*/
	if(chdir(argv[1])  == -1)
	{
		printf("no path found!\n");
		exit(1);
	}
	printf("change new path successful!\n");
	
	/* get current path*/
	if(getcwd(buf,SIZE) == NULL)
	{
		printf("print current path failed!\n");
		exit(1);
	}
	printf("current path is :%s\n",buf);
	
	int filedes[2] = {};
	if(pipe(filedes) != 0)
	{
		printf("creat pipe failed!\n");
		exit(1);
	}	
	printf("pipe discribe :%d --- %d\n",filedes[0],filedes[1]);
	
	return 0;
}

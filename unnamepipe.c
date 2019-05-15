#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 255
int main()
{
	int fd[2] = {};
	char buf[BUFSIZE] = {};
	int id = 0;
	
	// /*create pipe */
	// if(pipe(fd) < 0)
	// {
		// printf("create pipe failed !\n");
		// exit(1);
	// }
	
	// if((id = fork()) < 0)
	// {
		// printf("fork failed !\n");
		// exit(1);
	// }
	// /* write and read from two sides */
	// if(id == 0)
	// {
		// /* close pipe read side */
		// close(fd[0]);
		// write(fd[1],"hello world!\n",50);
	// }
	// else if(id > 0)
	// {
		// /* close pipe write side */
		// close(fd[1]);
		// read(fd[0],buf,BUFSIZE);
		// printf("%s",buf);
	// }
	// else
		// exit(1);
	
	if(pipe(fd) < 0)
	{
		exit(1);
	}
	
	if((id = fork()) < 0)
		exit(1);
	
	/* first child process */
	if(id == 0)
	{
		close(fd[0]);
		write(fd[1],"hello world!\n",50);
		exit(0);
	}	
	
	if((id = fork()) < 0)
		exit(1);
	
	/* second child process */
	if(id == 0)
	{
		close(fd[1]);
		read(fd[0],buf,BUFSIZE);
		printf("%s",buf);
		exit(0);
	}
	
	else if (id >0)
	{
		close(fd[0]);
		close(fd[1]);
		exit(0);
	}
	
	return 0;
}
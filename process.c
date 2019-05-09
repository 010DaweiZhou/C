#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
	/* count will be change when vfork , no change when fork*/
	unsigned char count = 0;
	int pid = getpid();
	printf("current process id : %d\n", pid);
	
	/* 
	   fork copy data fully, 
	   who will run first isn't sure.
	*/
	
	/*
	   vfork don't copy fully before exit and exec, 
	   child run first 
	*/
	int child = vfork();
	if(child == 0)
	{
		printf("I'm child  , count is :%d , value is : %d\n", count, child);
		printf("current process id : %d\n", getpid());
		/*father process would occur Segmentation fault without this  */
		exit(0);
	}
	else if(child > 0)
	{
		printf("I'm father , count is :%d , value is : %d\n", ++count, child);
		printf("current process id : %d\n", getpid());
	}
	else
	{
		printf("fork error! : %d\n", child);
		exit(1);
	}
	
	/* 2^n processes will generate !*/
	// fork();
	// fork();
	// printf("process running!%d\n",getpid());
	
	if((child = fork()) == 0)
	{
		/* if call this function , this process will not run the residual code*/
		if(execl("/bin/echo", "echo", "execute by execl", NULL))
			perror("error by execl");
	}
	
	/* if there are child process before this , this while not effective */
	//wait(NULL);
	waitpid(child,NULL,0);
	
	if(fork() == 0)
	{
		if(execlp("echo", "echo", "execute by execlp", NULL))
			perror("error by execlp");

	}
	
	if(fork() == 0)
	{
		if(execle("/bin/echo", "echo", "echo by execle", NULL, NULL))
			perror("error by execle");

	}
	
	// if(execl("/home/zhou/code/update.py", "update.py", NULL))
		// perror("error by execl");
	
	
	
	exit(0);
}
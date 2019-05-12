#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

void signal_handler(int signal)
{
	printf("I get ctrl+c !\n");
}

void signal_handler_new(int signal, siginfo_t * pInfo, void * reserved)
{
	static int x = 0;
	printf("I get %d times ctrl+c !\n",x++);
}

int main()
{
	int status = 0;
	pid_t id = 0 , child_id = 0;
	
	if((id = fork()) < 0)
		exit(1);
	
	if( id == 0)
	{
		printf("pid : %d \n" , getpid());
		printf("group id :%d\n",getpgrp());
		exit(3);
	}
	else
	{
		child_id = wait(&status);
		/* if hava status*/
		if(WIFEXITED(status))
		{
			printf("child process %d exit normally.\n",child_id);
			/* get status */
			printf("return code %d.\n",WEXITSTATUS(status));
		}
		else
		{
			printf("child process %d exit abnormally.\n",child_id);
		}
	}
	
	printf("%d\n",getuid());
	
	/* execute the system shell */
	status = system(NULL);
	if(status < 0)
	{
		printf("system error\n");
		exit(0);
	}
	
	status = system("date");
	if(status < 0)
	{
		printf("system error\n");
		exit(0);
	}
	
	printf("pid : %d \n" , getpid());
	printf("group id :%d\n",getpgrp());
	
	/* add the dispose function*/
	// printf("I'm waiting for Ctrl+\\ to exit\n");
	// signal(SIGINT,signal_handler);

	
	struct sigaction act ;
	act.sa_sigaction = signal_handler_new;
	act.sa_flags = SA_SIGINFO;
	/* empty the signal set */
	sigemptyset(&act.sa_mask);
	/* add block signal */
	sigaddset(&act_sa_mask,SIGQUIT);
	sigaction(SIGINT,&act,NULL);

	while(1)
	{
		sleep(2);
	}
	
	
	return 0;	
}
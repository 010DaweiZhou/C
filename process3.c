#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdlib.h>

void signal_handler(int signal, siginfo_t * info , void * reverse)
{
	printf("receive signal:%s",(char *)info->si_value.sival_ptr);
	return ;
}

void alarm_handler ()
{
	printf("hello !\n");
}

void timer_handler()
{
	/* setitimer function */
	static int times ;
	struct timeval tp;
	//struct tm * tm = NULL ;
	gettimeofday(&tp, NULL);
	//tm = localtime(&tp.tv_sec);
	printf("sec:%ld\t usec=%ld\n", tp.tv_sec , tp.tv_usec);
	
	if(times++ == 10)
		exit(0);
}

void initTimer(int tv_sec , int tv_usec)
{
	struct itimerval value = {};
	signal(SIGALRM,timer_handler);
	/* start timer after  tv_sec seconds */
	value.it_value.tv_sec = tv_sec;
	value.it_value.tv_usec = tv_usec;
	
	/* do function interval */
	value.it_interval.tv_sec = tv_sec;
	value.it_interval.tv_usec = tv_usec;
	setitimer(ITIMER_REAL, &value, NULL);
}

int main()
{
	
	pid_t pid = fork();
	
	if(pid < 0)
	{
		printf("fork error!\n");
		return -1;
	}
	else if(pid == 0)
	{
		printf("I'm child process\n");
		sleep(10);
		printf("I'm child process again\n");
		return 0;
	}
	else
	{
		printf("I'm father process\n");
		sleep(1);
		/* send abort to child */
		if(kill(pid,SIGABRT) == -1)
			printf("kill child failed!\n");
		
		
		int status = 0;
		/* get child status*/
		wait(&status);
		if(WIFSIGNALED(status))
			printf("child received signal already!\n");
		
		
		/* add signal dispose function*/
		struct sigaction act;
		act.sa_flags = SA_SIGINFO;
		act.sa_sigaction = signal_handler;
		sigemptyset(&act.sa_mask);
		if(sigaction(SIGUSR1,&act,NULL) == -1)
			exit(1);
		
		
		/* send signal to myself */
		char * buf = "I'm a linux C program!\n";
		sigval_t val;
		val.sival_ptr = buf;
		if(sigqueue(getpid(),SIGUSR1,val) == -1)
			exit(1);
		
		
		/* set an alarm a sec later do alarm_handler*/
		// signal(SIGALRM,alarm_handler);
		// alarm(1);
		// sleep(2);
		
		
		/* use setitimer function */
		initTimer(1,0);
		while(1)
		{
			
		}
		
		
		/* use raise() function to send a signal too myself*/
		printf("I'll kill myself!\n");
		raise(SIGABRT);
		printf("???");
		return 0;
	}
}
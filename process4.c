#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

/*  
	this function will not be called by ctrl+C forever
	beacuse it was blocked! 
*/
void signal_handler()
{
	printf("quit disposed!\n");
}

int main()
{
	/* init sigaction */
	struct sigaction act;
	act.sa_sigaction = signal_handler;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT,&act,NULL);
	
	
	/* set the block signal*/
	sigset_t sigset;
	sigemptyset(&sigset);
	sigaddset(&sigset,SIGINT);
	sigprocmask(SIG_BLOCK,&sigset,NULL);


	printf("sleep now...\n");
	//sleep(3);
	/* catch the alarm signal to awaken */
	signal(SIGALRM,signal_handler);
	alarm(3);
	printf("before\n");
	pause();
	printf("after\n");

	
	while(1)
	{
		sleep(3);
	}
	
	exit(0);
}
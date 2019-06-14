#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>


#define ERR_EXIT(m)\
	do\
	{\
		perror(m);\
		exit(EXIT_FAILURE);\
	}\
	while(0)
	


sigset_t mask = {};
pthread_mutex_t lock  = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int quitflag;

/* dispose the signal inherit from master thread */
void * sig_dispose (void * argv)
{
	int err = -1;
	int signo = 0;
	
	for(;;)
	{
		/*
			wait form signal specified by mask set .
			the signal will be set to signo
		*/
		err = sigwait(&mask , &signo);
		if(err != 0 )
			ERR_EXIT("sigwait");
		
		switch(signo)
		{
			case SIGINT:
				printf("sigint...\n");
				break;
			case SIGQUIT:
				printf("sigquit...\n");
				pthread_mutex_lock(&lock);
					quitflag = 1;
				pthread_mutex_unlock(&lock);
				pthread_cond_broadcast(&cond);
				return 0;
			default:
				printf("unknown sig...\n");
				exit(1);
		}
		
	}
}

int main(int argc , char ** argv)
{
	
	int err = -1;
	sigset_t oldmask = {};
	pthread_t id = 0;
	
	sigemptyset(&mask);
	sigaddset(&mask , SIGINT);
	sigaddset(&mask , SIGQUIT);
	
	/* the result is union of two sets and store in oldmask */
	err = pthread_sigmask(SIG_BLOCK, &mask, &oldmask);
	
	if(err)
	{
		ERR_EXIT("SIG_BLOCK error");
	}
	
	//if(memcmp(&mask , &oldmask , sizeof(sigset_t)))
	//	printf("two signal equal!\n");
		
	pthread_create(&id , NULL , sig_dispose, NULL);
	
	pthread_mutex_lock(&lock);
		while(quitflag == 0 )
			pthread_cond_wait(&cond , &lock);
	pthread_mutex_unlock(&lock);
	
	
	quitflag = 0;
	
	/* clean up oldmask */
	err = sigprocmask(SIG_SETMASK, &oldmask , NULL);
	
	if(err)
		ERR_EXIT("sigprocmask err!");
	
	
	exit(0);
}
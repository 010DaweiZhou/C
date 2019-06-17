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
	
pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;


void prepare()
{
	printf("prepare...\n");
	pthread_mutex_lock(&lock1);
	pthread_mutex_lock(&lock2);
}

void child()
{
	printf("child...\n");
	pthread_mutex_unlock(&lock1);
	pthread_mutex_unlock(&lock2);
}

void parent()
{
	printf("parent...\n");
	pthread_mutex_unlock(&lock1);
	pthread_mutex_unlock(&lock2);
}

/* here , thre child process only have this thread */
void * thread_dispose(void * arg)
{
	pid_t process_id;
	process_id = fork();
	
	if(process_id != 0)
		pthread_exit(NULL);
	
	/* parent process can't arrive here */
	printf("pid = %d\n",getpid());
}

int main(int argc , char ** argv)
{
	
	pthread_t thread_id ;
	
	printf("parent pid = %d\n",getpid());
	pthread_atfork(prepare,child,parent);
	
	pthread_create(&thread_id ,NULL ,thread_dispose ,NULL);
	
	sleep(1);
	
	/* child process can't arrive here */
	printf("pid = %d\n",getpid());
	
	pthread_mutex_destroy(&lock1);
	pthread_mutex_destroy(&lock2);
	
	exit(0);
}
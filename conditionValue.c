#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct msg {
	int i;
};

struct msg queue = {0};
/* initialize lock */
pthread_cond_t qready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

/* callback to release the lock */
void my_cleanup()
{
	printf("my cleanup...\n");
	pthread_mutex_unlock(&qlock);
}

void * thread_append(void * arg)
{
	int i = 0;
	
	for(i ; i < 10 ; i++)
	{	
		pthread_mutex_lock(&qlock);
		/* set value */
		queue.i = i;
		
		pthread_mutex_unlock(&qlock);
		
		printf("send notify...\n");
		
		/* send notify to rouse all threads which are waiting notify */
		pthread_cond_broadcast(&qready);
		sleep(1);
	}
	pthread_exit(NULL);
}

void * thread_dispose(void * arg)
{
	pthread_cleanup_push(my_cleanup,(void *)&qlock);
	for(;;)
	{
		pthread_mutex_lock(&qlock);
		
		/* unlock and put the thread in the queue for waiting the notify */
		pthread_cond_wait(&qready,&qlock);
		printf("Get value! %d\n",queue.i);
		pthread_mutex_unlock(&qlock);
	}
	pthread_cleanup_pop(0);
	pthread_exit(NULL);
}


int main(int argc , char ** argv)
{
	pthread_t append_thread = 0;
	pthread_t dispose_thread = 0;
	
	pthread_create(&append_thread,NULL,thread_append,NULL);
	pthread_create(&dispose_thread,NULL,thread_dispose,NULL);
	// pthread_t dispose_thread = pthread_create();
	
	printf("Join...\n");
	pthread_join(append_thread,NULL);
	
	printf("Cancel dispose...\n");
	pthread_cancel(dispose_thread);
	
	/* cleanup lock */
	pthread_cond_destroy(&qready);
	pthread_mutex_destroy(&qlock);
	
	exit(0);
}
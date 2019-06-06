#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/* two read threads and one write thread */
pthread_t read_thread  = 0;
pthread_t third_thread  = 0;
pthread_t write_thread = 0;

/* value is operated by three threads */
int x = 100;

/* read write lock , only read threads are concurrent */
pthread_rwlock_t lock = {0};

void * rdthread(void * arg)
{
	int i = 0;
	/* 
		get read lock , 
		write thread would be blocked if get the lock.
		but other read threads will not be influenced.
	*/
	pthread_rwlock_rdlock(&lock);
	printf("thread %lu get readlock!\n",pthread_self());
	for(i = 0 ;i<10 ;i++)
	{
		printf("x = %d\n",x);
	}
	pthread_rwlock_unlock(&lock);
	pthread_exit(NULL);
}

void * wrthread(void * arg)
{
	int i = 0;
	/* get write lock , read threads would be blocked if get the lock*/
	pthread_rwlock_wrlock(&lock);
	printf("thread %lu get write!\n",pthread_self());
	for(i = 0 ;i<10 ;i++)
	{
		x++;
	}
	/* release the write lock */
	pthread_rwlock_unlock(&lock);
	pthread_exit(NULL);
}

int main(int argc , char ** argv)
{
	int ret = 0;
	/* init read write lock */
	ret = pthread_rwlock_init(&lock,NULL);
	 
	if(ret != 0 )
		 exit(1);
	 
	pthread_create(&write_thread ,NULL ,wrthread ,NULL);
	pthread_create(&read_thread ,NULL ,rdthread ,NULL);
	pthread_create(&third_thread ,NULL ,rdthread ,NULL);
	
	pthread_join(read_thread,NULL);
	pthread_join(third_thread,NULL);
	pthread_join(write_thread,NULL);
	
	printf("main x = %d\n",x);
	
	/* destroy the read write lock */
	pthread_rwlock_destroy(&lock);
}
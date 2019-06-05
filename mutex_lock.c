#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


struct fd_lock
{
	u_int8_t count;
	pthread_mutex_t lock;
};

int i = 0;
//static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock ;

void my_unlock(void * lock)
{
	pthread_mutex_unlock(lock);
}


void * thread1(void * arg)
{
	int a = 0;
	
	/* add cleanup function when get pthread cancel */
	pthread_cleanup_push(my_unlock,(void *)&lock);
	/* try to get lock */
	pthread_mutex_lock(&lock);
	
	/* for pthread cancel */
	sleep(1);
	for(a = 0; a <100000; a++)
	{
		i++;
	}
	
	/* unlock */
	pthread_mutex_unlock(&lock);
	pthread_cleanup_pop(0);
	pthread_exit(NULL);
}

void * thread2(void * arg)
{
	int a = 0;
	
	pthread_cleanup_push(my_unlock,(void * )&lock);
	/* try to get lock */
	pthread_mutex_lock(&lock);
	sleep(1);
	for(a = 0;a <100000;a++)
	{
		i++;
	}
	
	pthread_mutex_unlock(&lock);
	pthread_cleanup_pop(0);
	pthread_exit(NULL);
}


int main(int argc , char ** argv)
{
	void * ret ;
	pthread_t thread1_id = 0;
	pthread_t thread2_id = 0;
	
	/* init the lock */
	pthread_mutex_init(&lock ,NULL );
	
	/* create two thread to handle a whole situation value */
	pthread_create(&thread1_id,NULL,thread1, NULL);
	pthread_create(&thread2_id,NULL,thread2, NULL);
	
	if(thread1_id <= 0 ||thread2_id <= 0)
		exit(1);
	
	printf("1:%lu , 2:%lu\n",thread1_id, thread2_id);
	
	/* wait two thread end */
	pthread_cancel(thread1_id);
	printf("wait for thread 1\n");
	pthread_join(thread1_id, &ret);
	//pthread_cancel(thread2_id);
	printf("wait for thread 2\n");
	pthread_join(thread2_id, &ret);
	
	pthread_mutex_destroy(&lock);
	
	printf("i = %d\n",i);
	exit(0);
}
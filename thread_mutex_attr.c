#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

pthread_mutexattr_t attr;
pthread_mutex_t lock ;

void b_fun ()
{
	pthread_mutex_lock(&lock);
	printf("b ....\n");
	sleep(1);
	pthread_mutex_unlock(&lock);
}

/* a can call b without block beacuse recursive lock */
void a_fun ()
{
	pthread_mutex_lock(&lock);
	printf("a call b ....\n");
	b_fun();
	sleep(1);
	pthread_mutex_unlock(&lock);
}

void * a (void * arg)
{
	a_fun();
}

void * b (void * arg)
{
	b_fun();
}


int main(int argc,char ** argv)
{
	pthread_t id_a;
	pthread_t id_b;
	
	pthread_mutexattr_init(&attr);
	/* 
		set lock's type recursive in order to get lock many times .
		if there are teo functions , a and b , a call b ,
		they have the same lock object.
		one thread can call function b directly when calling function a .
	*/
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&lock ,&attr);
	
	/* first lock */
	pthread_mutex_lock(&lock);
	
	/* a thread is created , but a can't get the lock */
	pthread_create(&id_a ,NULL ,a ,NULL);
	
	/* second lock , can get lock directly beacuse of PTHREAD_MUTEX_RECURSIVE*/
	pthread_mutex_lock(&lock);
		pthread_create(&id_b ,NULL ,b ,NULL);
	/* second lock free */
	pthread_mutex_unlock(&lock);
	
	/* first lock free */
	pthread_mutex_unlock(&lock);
	
	/* a and b will contend the lock here */
	pthread_join(id_a, NULL);
	pthread_join(id_b, NULL);

	
	/* 
		read write lock have an attribute is SHARED ,default !shared 
	*/
	int property;
	pthread_rwlockattr_t  rw_attr;
	
	pthread_rwlockattr_init(&rw_attr);
	pthread_rwlockattr_getpshared(&rw_attr,&property);
	printf("rwlock default = %d ,shared =  %d\n",property, PTHREAD_PROCESS_SHARED);
	pthread_rwlockattr_setpshared(&rw_attr,PTHREAD_PROCESS_SHARED);
	pthread_rwlockattr_getpshared(&rw_attr,&property);
	printf("rwlock set property = %d , shared = %d\n",property, PTHREAD_PROCESS_SHARED);
	
	
	/* 
		conditional value have an attribute is SHARED ,default !shared 
	*/
	property = 0;
	pthread_condattr_t cattr;
	pthread_condattr_init(&cattr);
	pthread_condattr_getpshared(&cattr, &property);
	printf("condtion default = %d ,shared =  %d\n",property, PTHREAD_PROCESS_SHARED);
	pthread_condattr_setpshared(&cattr, PTHREAD_PROCESS_SHARED);
	pthread_condattr_getpshared(&cattr, &property);
	printf("condtion set property = %d , shared = %d\n",property, PTHREAD_PROCESS_SHARED);
	
	
	/* cleanup */
	pthread_mutexattr_destroy(&attr);
	pthread_mutex_destroy(&lock);
	pthread_rwlockattr_destroy(&rw_attr);
	pthread_condattr_destroy(&cattr);
	
	exit(0);
}
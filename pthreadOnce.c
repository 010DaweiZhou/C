#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

pthread_mutex_t lock;
/* 
	once_control must be a global(static) variable
	and must be PTHREAD_ONCE_INIT
*/
static pthread_once_t once_control = PTHREAD_ONCE_INIT;
static pthread_key_t key ;


void * dispose (void * arg)
{
	int old_type;
	int old_state;
	/* thread can be cancel whenever */
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &old_type);
	/* accept cancel */
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE , &old_state);
	
	/* thread will be cancel at cancel point */
	//pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED , &old_type);
	
	/* ignore the cancel */
	//pthread_setcancelstate(PTHREAD_CANCEL_DISABLE , &old_state);
	
	printf("dispose...\n");
	pthread_testcancel();
	
	printf("sleep...\n");
	/* cancel point */
	sleep(1);
	
	printf("exit normally...\n");
	pthread_exit(NULL);
	
}

void thread_init()
{
	pthread_mutexattr_t mutexattr;
	pthread_mutexattr_init(&mutexattr);
	pthread_mutexattr_settype(&mutexattr,PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&lock, &mutexattr);
	pthread_mutexattr_destroy(&mutexattr);
}

int main(int argc , char ** argv)
{
	/* the process call thread init function once only */
	pthread_once(&once_control , thread_init);
	
	pthread_t id = 0;
	
	pthread_create(&id, NULL , dispose , NULL);
	
	pthread_cancel(id);
	
	//pthread_join(id , NULL);
	
	pthread_mutex_destroy(&lock);
	
	exit(0);
}
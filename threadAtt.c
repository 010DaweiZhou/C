#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

void * my_dispose(void * arg)
{
	printf("hello world !\n");
	pthread_exit(NULL);
}

int main(int argc,char ** argv)
{
	pthread_t id = 0;
	pthread_attr_t attr = {};
	
	pthread_attr_init(&attr);
	
	/* two functions have same result */
	//pthread_detach(id);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	
	//pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	pthread_create(&id ,&attr, my_dispose, NULL);
	
	int x = 0;
	pthread_attr_getdetachstate(&attr, &x);
	printf("detachstate = %d\n",x);
	
	size_t size = 0;
	pthread_attr_getstacksize(&attr,&size);
	printf("stacksize = %ld\n",size);
	/* if PTHREAD_CREATE_DETACHED , join will return failed*/
	//pthread_join(id , NULL);
	
	int concurrency = pthread_getconcurrency();
	printf("concurrency = %d\n",concurrency);
	
	pthread_attr_destroy(&attr);
	exit(0);
}
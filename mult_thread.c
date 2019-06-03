#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

struct ret 
{
	int a;
	int b;
};

void clean_up(void * x)
{
	printf("%s thread will exit now!\n", (char *)x);
}


void * thread1(void * arg)
{
	int i = 0;
	
	pthread_cleanup_push(clean_up , "hello");
	
	if(arg)
	{
		/* return will not call the cleanup function */
		//return NULL;
		pthread_exit(NULL);
	}
	
	pthread_cleanup_pop(0);
	
	for(i = 0 ; i < 3 ; i ++)
	{
		printf("thread id = %lu\n",pthread_self());
		sleep(1);
	}
	
	//printf("thread %lu exit\n",pthread_self());
	
	// struct ret * my_ret = (struct ret *)malloc(sizeof(struct ret));
	// my_ret->a = 1;
	// my_ret->b = 2;
	char buf[50] = "hello world !";
	char * temp = (char *)malloc(sizeof(buf));
	strcpy(temp , buf);
	
	/* two method is with the same result */
	//return ((void *)1);
	pthread_exit((void *)temp);
}

int main(int argc , char ** argv)
{
	int ret = -1;
	void * thread_ret = NULL;
	pthread_t thread_number = -1;
	
	//ret = pthread_create(&thread_number, NULL, thread1, (void *)1);
	ret = pthread_create(&thread_number, NULL, thread1, NULL);
	printf("new thread id = %lu\n",thread_number);
	/* the second parameter is a **  */
	pthread_join(thread_number,&thread_ret);
	
	
	/* we can get the return value form thread
		by malloc memery or a whole situation value ,
		include value ,struct ,string and so on
	*/
	//printf("thread return %lu\n",(unsigned long)thread_ret);
	// struct ret * buf = (struct ret* )thread_ret;
	// printf("a=%d,b=%d\n", buf->a, buf->b);
	char * buf = (char * ) thread_ret;
	if(!buf)
		exit(1);
	
	printf("%s\n",buf);
	free(buf);
	buf = NULL;
	exit(0);
}


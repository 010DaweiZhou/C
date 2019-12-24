#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

void cleanup(void * arg)
{
    printf("%s\n",(char *)arg);
}


void * func2(void * arg)
{
    printf("child 2 push start\n");
    pthread_cleanup_push(cleanup, "child 2 first  push\n" );
    pthread_cleanup_push(cleanup, "child 2 second push\n");
    printf("child 2 push finished\n");
    
    if(arg)
        return NULL ;
    
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    
    printf("child 2 exit!\n ");
    return NULL ;
}


void * func1(void * arg)
{
    printf("child 1 push start\n");
    pthread_cleanup_push(cleanup, "child 1 first push\n" );
    pthread_cleanup_push(cleanup, "child 1 second push\n");
    printf("child 1 push finished\n");
    
    if(arg)
        pthread_exit(NULL);
    
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    
    printf("child 1 exit!\n ");
    pthread_exit(NULL);
}


int main(int arghc ,char ** argv)
{
    pthread_t id1 = {0};
    pthread_t id2 = {0};
    
    pthread_create(&id1,NULL,func1,(void *)1);
    pthread_create(&id2,NULL,func2,(void *)1);
    
    pthread_join(id1,NULL);
    pthread_join(id2,NULL);
    
    printf("main exit!\n");
    exit(0);
}
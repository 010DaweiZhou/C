#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

struct msg{
    struct msg * next;
    int data ;
};

struct msg * workq;

void * process_msg(void * arg)
{
    struct msg * msg = NULL;
    
    for(;;)
    {
        pthread_mutex_lock(&lock);
        
        while(workq == NULL)
        {
            pthread_cond_wait(&condition,&lock);
        }
        
        msg = workq;
        
        workq = workq->next;
        printf("%d\n",msg->data);
        
        free(msg);
        msg = NULL;
        
        pthread_mutex_unlock(&lock);
    }
}

void * add_msg(void * arg)
{ 
    struct msg * temp = NULL;
    /* can't do this here , maybe workq are freed*/
    //struct msg * node = workq;
    struct msg * node = NULL;
    
    //for(;;)
    //{
    //    sleep(1);  
        temp = malloc(sizeof(struct msg));
        memset(temp , 0 ,sizeof(struct msg));
        temp->data = *(int *)arg;
        
        pthread_mutex_lock(&lock);
        
        if(workq == NULL)
        {
            workq = temp;
        }
        else
        {
            /* we should get workq here */
            node = workq;
            while(node->next != NULL)
            {
                node = node->next;
            }
            
            node->next = temp;
        }
        
        temp = NULL;
        pthread_cond_signal(&condition);
        pthread_mutex_unlock(&lock);
        
    //}
}

int main(int argc ,char ** argv)
{
    int i = 0;
    pthread_t process = {0};
    //pthread_t add1 = {0};
    
    pthread_create(&process,NULL,process_msg,NULL);
    //pthread_create(&add1,NULL,add_msg,NULL);
    

    for (i = 0 ; i < 100000; i++)
    {
        add_msg((void *)&i);
        //sleep(1);
    }
    
    sleep(5);
    exit(0);
}
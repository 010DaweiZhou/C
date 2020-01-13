#ifndef THREAD_POOL_H
#define THREAD_POOL_H

/* I like do this */
#define ISIS_MALLOC(T,P,N)                              \
do{                                                     \
    if(!P)                                              \
    {                                                   \
        while((P = (T*)malloc(sizeof(T) * N)) == NULL)  \
        {                                               \
            usleep(1000);                               \
        }                                               \
        printf("malloc %lu \n",sizeof(T) * N);          \
        memset(P,0,sizeof(T) * N);                      \
    }                                                   \
}while(0)
    

typedef struct thread_pool_task_t_{
    /* function for dealing task */
    void * ( *function)(void *);
    /* task's parameter */
    void * arg;
}thread_pool_task_t;


typedef struct thread_pool_t_{
    /* protect variables of pool */
    pthread_mutex_t lock;
    /* protect busy number of pool */
    pthread_mutex_t thread_counter;
    /* task queue status */
    pthread_cond_t queue_not_full;
    pthread_cond_t queue_not_empty;
  
    /* thread queue */
    pthread_t  * pthreads;
    /* administrator  thread */
    pthread_t admin_tid;
    
    /* constant  */
    uint32_t min_thread_num;
    uint32_t max_thread_num;
    
    /* can be change */
    uint32_t live_thread_num;
    uint32_t busy_thread_num;
    uint32_t wait_exit_thread_num;
    
    /* task queue */
    thread_pool_task_t * task_queue;
    /* constant  */
    uint32_t task_queue_max_size;
    
    /* can be change */
    uint32_t task_queue_hread;
    uint32_t task_queue_tail;
    uint32_t task_queue_size;
    
    /* pool status */ 
    bool shutdown;
    
}thread_pool_t;


#endif
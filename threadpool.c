#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include "threadpool.h"

pthread_spinlock_t spin ;
uint32_t call_times = 0;

void * printf_func(void * arg)
{
    pthread_spin_lock(&spin);
    call_times++;
    pthread_spin_unlock(&spin);
    sleep(DEFAULT_TIME);
    return NULL;
}


void * threadpool_thread(void * arg)
{
    thread_pool_t * pool = (thread_pool_t *) arg;
    thread_pool_task_t task ;
    //signal(0, signal_handler);
    
    while(true)
    {
        pthread_mutex_lock(&pool->lock);
        
        /* pool is no shutdown , but no task , shell I kill myself ??? */
        while(pool->task_queue_size == 0 && pool->shutdown == false)
        {
            pthread_cond_wait(&pool->queue_not_empty,&pool->lock);
            
            /* too many thread should exit . */
            if(pool->wait_exit_thread_num > 0)
            {
                /* kill myself when live >= min  */
                if(pool->live_thread_num > pool->min_thread_num)
                {
                    pool->wait_exit_thread_num--;
                    pool->live_thread_num--;
                    pthread_mutex_unlock(&pool->lock);
                    pthread_exit(NULL);
                }
            }
        }
        
        /* pool is shutdown , kill self */
        if(pool->shutdown == true)
        {
            pthread_mutex_unlock(&pool->lock);
            pthread_exit(NULL);
        }
        
        /* get task from queue */
        task.function = pool->task_queue[pool->task_queue_head].function;
        task.arg = pool->task_queue[pool->task_queue_head].arg;
        
        pool->task_queue_head = (pool->task_queue_head + 1) % pool->task_queue_max_size;
        pool->task_queue_size--;
        
        pthread_cond_broadcast(&pool->queue_not_full);
        pthread_mutex_unlock(&pool->lock);
        
        
        /* do task */
        pthread_spin_lock(&pool->thread_counter);
        pool->busy_thread_num++;
        pthread_spin_unlock(&pool->thread_counter);
        
        (*(task.function))(task.arg);
        
        pthread_spin_lock(&pool->thread_counter);
        pool->busy_thread_num--;
        pthread_spin_unlock(&pool->thread_counter);
    }

    pthread_exit(NULL);
}


int is_thread_alive(pthread_t tid)
{
    return pthread_kill(tid,0) == ESRCH ? false : true;
}


void * admin_thread(void * arg)
{
    int i = 0;
    int add = 0;
    int queue_size = 0;
    int busy_num = 0;
    int live_num = 0;
    
    thread_pool_t * pool = (thread_pool_t *) arg;
    
    while(pool->shutdown == false)
    {
        sleep(DEFAULT_TIME);
        pthread_mutex_lock(&pool->lock);
        queue_size = pool->task_queue_size;
        live_num = pool->live_thread_num;
        pthread_mutex_unlock(&pool->lock);
        
        pthread_spin_lock(&pool->thread_counter);
        busy_num = pool->busy_thread_num;
        pthread_spin_unlock(&pool->thread_counter);
        
        if(queue_size > MIN_WAIT_TASK_NUM && live_num < pool->max_thread_num)
        {
            pthread_mutex_lock(&pool->lock);
            add = 0;
            
            for(i = 0; i < pool->max_thread_num && add < DEFAULT_THREAD_NUM && 
                        pool->live_thread_num < pool->max_thread_num; i++)
            {
                if(pool->pthreads[i] == 0 || is_thread_alive(pool->pthreads[i]) == false)
                {
                    pthread_create(&pool->pthreads[i],NULL,threadpool_thread,(void *)pool);
                    add++;
                    printf("admin thread add \n");
                    pool->live_thread_num++;
                }
            }
            pthread_mutex_unlock(&pool->lock);
        }
        
        if(busy_num * 2 < live_num && live_num > pool->min_thread_num)
        {
            pthread_mutex_lock(&pool->lock);
            pool->wait_exit_thread_num = DEFAULT_THREAD_NUM;
            
            for(i = 0 ; i < DEFAULT_THREAD_NUM ; i++)
            {
                pthread_cond_signal(&pool->queue_not_empty);
                printf("admin thread clear \n");
            }
            pthread_mutex_unlock(&pool->lock);
        }
    }
    
    pthread_exit(NULL);
}



thread_pool_t * threadpool_create(uint32_t thread_max,
                        uint32_t thread_min , uint32_t task_queue_max )
{
    int i = 0;
    thread_pool_t * pool = NULL;

    ISIS_MALLOC(thread_pool_t,pool,1);
    ISIS_MALLOC(pthread_t,pool->pthreads,thread_max);
    ISIS_MALLOC(thread_pool_task_t,pool->task_queue,task_queue_max);

    pool->min_thread_num = thread_min;
    pool->max_thread_num = thread_max;
    pool->live_thread_num = thread_min;
    pool->task_queue_max_size = task_queue_max;
    
    pthread_mutex_init(&pool->lock,NULL);
    pthread_spin_init(&pool->thread_counter,0);
    pthread_cond_init(&pool->queue_not_full,NULL);
    pthread_cond_init(&pool->queue_not_empty,NULL);
    
    /* create less thread at beginning */
    for(i = 0 ; i < thread_min ; i++)
    {
        pthread_create(&pool->pthreads[i], NULL, threadpool_thread, (void *)pool);
    }
    
    pthread_create(&pool->admin_tid, NULL, admin_thread, (void *)pool);
    
    return pool;
}


int threadpool_free(thread_pool_t * pool)
{
    int i = 0;
    
    if(pool == NULL)
        return 0;
   
    while(pool->task_queue_size != 0)
        usleep(1);
    
    pool->shutdown = true;
    
    if(pool->live_thread_num > 0)
    {
        pthread_cond_broadcast(&pool->queue_not_empty);
    }
    
    for(i = 0 ; i < pool->live_thread_num ; i++)
    {
        pthread_join(pool->pthreads[i],NULL);
    }
    
    if(pool->pthreads)
    {
        free(pool->pthreads);
        pool->pthreads = NULL;
    }
    
    if(pool->task_queue)
    {
        free(pool->task_queue);
        pool->task_queue = NULL;
    }

    pthread_mutex_lock(&pool->lock);
    pthread_mutex_destroy(&pool->lock);
    
    pthread_spin_lock(&pool->thread_counter);
    pthread_spin_destroy(&pool->thread_counter);
    
    pthread_cond_destroy(&pool->queue_not_full);
    pthread_cond_destroy(&pool->queue_not_empty);

    free(pool);
    pool = NULL;
    return 0;
}



int task_add(thread_pool_t * pool , void * function , void * arg)
{
    pthread_mutex_lock(&pool->lock);
    
    while(pool->shutdown == false && pool->task_queue_max_size == pool->task_queue_size)
    {
        pthread_cond_wait(&pool->queue_not_full , &pool->lock);
    }
    
    if(pool->shutdown == true)
    {
        pthread_mutex_unlock(&pool->lock);
        return -1;
    }
    
    pool->task_queue[pool->task_queue_tail].function = function ;
    pool->task_queue[pool->task_queue_tail].arg = arg;
    
    pool->task_queue_tail = (pool->task_queue_tail + 1) % pool->task_queue_max_size;
    pool->task_queue_size++;
    
    pthread_cond_signal(&pool->queue_not_empty);
    pthread_mutex_unlock(&pool->lock);
    
    return 0 ;
}



int main(int argc , char ** argv)
{
    int i = 50;

    pthread_spin_init(&spin,0);
    thread_pool_t * pool = threadpool_create(MAX_THREAD_NUM,DEFAULT_THREAD_NUM,QUEUE_SIZE);
    
    while(i-- > 0)
        task_add(pool , printf_func , "hello world!");

    sleep(10);
    
    i = 50;
    while(i-- > 0)
        task_add(pool , printf_func , "hello world!");
    
    threadpool_free(pool);
    printf("%d\n",call_times);
    exit(0);
}
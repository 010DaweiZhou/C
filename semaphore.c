#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PATHNAME "generic.h"


union semun
{
	int val;
	struct semid_ds * buf;
	unsigned short * array;
};

/* init the semaphore */
int set_semvalue(int sem_id)
{
	union semun sem;
	sem.val = 1;
	
	if(semctl(sem_id,0,SETVAL,sem) == -1)
		return -1;
	
	return 0;
	
}

int semaphore_p(int sem_id)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = -1;
	sem_b.sem_flg = SEM_UNDO;
	
	if(semop(sem_id, &sem_b, 1) == -1)
	{
		printf("semaphore p failed!\n");
		return -1;
	}
	return 0;
}

int semaphore_v(int sem_id)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = 1;
	sem_b.sem_flg = SEM_UNDO;
	
	if(semop(sem_id, &sem_b, 1) == -1)
	{
		printf("semaphore v failed!\n");
		return -1;
	}
	return 0;
}

int main(int argc , char ** argv)
{
	int semaphore_id = 0;
	char message = 'X';
	
	/* assign a key , or use ftok(file to key) */
	//key_t key = ftok(PATHNAME, 1);
	key_t key = 1234;
	
	/* create semaphore if no exist. use if exist*/
	semaphore_id = semget(key, 1, IPC_CREAT | 0666);
	
	if(semaphore_id < 0)
		exit(1);
	
	/* first process init the semaphore */
	if(argc > 1)
	{
		if(set_semvalue(semaphore_id) == -1)
			exit(1);
		
		message = argv[1][0];
		sleep(1);
	}
	
	/* two process use the semaphore , message is different */
	int i = 0;
	for (i = 0 ; i < 10 ; i++)
	{
		if(semaphore_p(semaphore_id) == -1)
			exit(1);
		
		/* synchronized dispose */
		printf("%c",message);
		fflush(stdout);
		sleep(1);
		
		if(semaphore_v(semaphore_id) == -1)
			exit(1);
	}
	
	
	if(argc == 1)
	{
		exit(0);
	}
	
	printf("\n");
	sleep(1);
	/* delete the semaphore */
	if(semctl(semaphore_id, 0, IPC_RMID, NULL) == -1)
	{
		printf("delete error!\n");
		exit(1);
	}
	
	printf("delete success!\n");
	return 0;
}


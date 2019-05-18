#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 4096
#define NAMESIZE 10
struct people {
	unsigned char age;
	char name[NAMESIZE];
};

int main()
{
	int pid = 0;
	int shm_id;
	
	/* create the sharememery first*/
	shm_id = shmget(IPC_PRIVATE, BUFSIZE, 0666);
	
	if(shm_id < 0 )
		exit (1);
	
	printf("shm_id = %d\n", shm_id);
	
	/* create the new process */
	pid = fork();
	
	if(pid < 0 )
	{
		exit(1);
	}
	/* child process write to sharememery */
	else if(pid == 0)
	{
		int i = 0;
		char chr = 'a';
		struct people * man = NULL;
		struct people temp = {};
		
		/* map the sharememery */
		man = (struct people *)shmat( shm_id, NULL, 0);

		/* write to memery */
		for (i = 0; i < 5; i++)
		{
			memcpy(man->name, &chr, 1);
			man->age = i;
			chr++;
			man++ ;
		}
		
		/* separate the sharememery */
		shmdt(man);
		exit(0);
	}
	/* father process read from sharememery */
	else if (pid > 0)
	{
		/* 
			only reading data after the child process writed .
			reading no data if the child have not writen yet.
		*/
		sleep(1);
		int a = 0;
		struct people * father;
		
		/* map the sharememery */
		father = (struct people *)shmat( shm_id, NULL, 0);
		
		/* read from memery */
		for(a = 0; a < 5; a++)
		{
			printf("name = %s , age = %d\n" , father->name, father->age);
			father++;
		}
		
		/* separate the sharememery */
		shmdt(father);
		
		/* delete the memery at last */
		shmctl(shm_id, IPC_RMID, NULL);
		
		exit(0);
	}
	
	return 0;
}

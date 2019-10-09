#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mallco_total = 0;
int free_total = 0;


struct hash_bucket{
	int data;
};


#define HASH_SIZE 1024

unsigned int times33(char * key)
{
	unsigned int hash = 5381;
	while( *key )
	{
		printf("hash = %10u , *key = %d \n",hash, *key);
		hash += (hash << 5) + (*key++);
	}
	return hash;
}

int main(int argc , char ** argv)
{
	int data = 1;
	unsigned int index = -1;
	int i = 0;
	
	char * key = "hello world!";
	
	struct hash_bucket ** hash_table = NULL;
	
	hash_table = malloc(sizeof(struct hash_bucket *) * HASH_SIZE);
	mallco_total += sizeof(struct hash_bucket *) * HASH_SIZE;
	memset(hash_table, 0 , sizeof(struct hash_bucket *) * HASH_SIZE);
	index = times33(key);

	printf("index = %d\n", index % HASH_SIZE);
	
	struct hash_bucket * node = malloc(sizeof(struct hash_bucket));
	mallco_total += sizeof(struct hash_bucket);
	
	hash_table[index % HASH_SIZE] = node;
	node->data = 1;
	
	for(i = 0 ; i < HASH_SIZE ; i++)
	{
		if(hash_table[i] != NULL)
		{
			printf("data = %d\n", hash_table[i]->data);
		}
	}
	
	for(i = 0 ; i < HASH_SIZE ; i++)
	{
		if(hash_table[i] != NULL)
		{
			free(hash_table[i]);
			free_total += sizeof(struct hash_bucket);
			hash_table[i] = NULL;
		}
	}
	
	free(hash_table);
	free_total += sizeof(struct hash_bucket *) * HASH_SIZE;
	hash_table = NULL;
	
	printf("mallco_total = %d , free_total = %d\n" , mallco_total , free_total);
	
	return 0;
}
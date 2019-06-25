#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simpleHash.h"

unsigned int hash33(char * key)
{
	unsigned int hash = 0;
	/* here need (*key) rather than (key) */
	while(*key)
		hash = (hash << 5) + hash + *key++;
	return hash;
}

/*
	create a hash table and hash bucket
*/
HashTable* hash_table_init()
{
	/*malloc for hash table */
	HashTable* ht = (HashTable *)malloc(sizeof(HashTable));
	if(ht == NULL)
	{
		printf("malloc error!/n");
		return NULL;
	}

	
	/* malloc for table bucket , total number is HASH_SIZE */
	ht->table = (HashNode **)malloc(sizeof(HashNode *) * HASH_SIZE);
	if(ht->table == NULL)
	{
		printf("malloc error!\n");
		free(ht);
		return NULL;
	}

	memset(ht->table , 0 ,sizeof(HashNode*) * HASH_SIZE );
	return ht;
}

/*
	delete the hash table and hash bucket,free all node if existed
*/
int hash_table_delete(HashTable* ht)
{
	if(ht == NULL)
	{
		printf("ht is NULL!\n");
		return 0;
	}

	if(ht->table == NULL)
	{
		printf("ht->table is NULL!\n");
		free(ht);
		return 0;
	}	
	
	for(int i = 0 ; i<HASH_SIZE ; i++)
	{	
		HashNode * p = ht->table[i];
		
		if(p)
		{
			/* free node here */
			free(p);
			p = NULL;
		}
	}
	
	/* free table */
	free(ht->table);
	ht->table = NULL;
	
	free(ht);
	ht = NULL;
	return 0;
}

/*
	get hash node data 
*/
void * hash_get(HashTable* ht ,char * key)
{
	unsigned int i = hash33(key) % HASH_SIZE;
	HashNode* p = ht->table[i];
	
	if(p && p->data)
		return p->data;
	else
		return NULL;
}

/*
	put data into hash node
*/
int hash_put(HashTable* ht , char * key,void * data)
{
	unsigned int i = hash33(key) % HASH_SIZE;
	HashNode* p = ht->table[i];
	
	if(p == NULL)
	{
		/* p will be free when delete hash table */
		p = (HashNode *)malloc(sizeof(HashNode));
	}
	/* data will be free be by user */
	p->data = data;
	/* It's import to put p back , otherwise table[i] will be NULL */
	ht->table[i] = p;
}

#if 0
int main(int argc , char ** argv)
{
	int ret = -1;
	HashTable* ht = hash_table_init();
	
	
	int * data = (int * )malloc(sizeof(int));
	*data = 10;
	hash_put(ht,"hello",data);
	
	
	int * read_data = hash_get(ht,"hello");
	printf("%d\n",*read_data);
	free(read_data);
	
	ret = hash_table_delete(ht);
	exit(0);
}
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "6.h"

int malloc_total = 0;
int free_total = 0;

node * insert(struct list * list,void * data)
{
	node * next_node = NULL;
	node * list_node = NULL;
	
	if(list == NULL)
	{
		return NULL;
	}
	
	list_node = (node *)malloc(sizeof(node));
	malloc_total += sizeof(list_node);
	
	memset(list_node,0,sizeof(node));
	list_node->next = NULL;
	list_node->data = data;
	
	// if the head is null ,the new node is head
	if(list->head == NULL)
	{
		list->head = list_node;
		(list->count)++;
	}
	else
	{
		//first one
		next_node = list->head;
		
		// find the node whose next is null ,it's the last one
		while(next_node->next != NULL)
			next_node = next_node->next;
		
		//insert the new node behind the last one
		next_node->next = list_node ;
		(list->count)++;
	}
	
	return list_node;
}


int freeList(struct list * list,size_t size)
{
	node * next = NULL;
	
	if(list == NULL)
		return 0;
	
	node * next_node = list->head;
	
	if(next_node == NULL)
	{
		free_total += sizeof(struct list);
		free(list);
		return 0;
	}	
	
	while(next_node->next != NULL)
	{
		next = next_node->next;
		
		free_total += size;
		free(next_node->data);
		
		free_total += sizeof(next_node);
		free(next_node);
		
		(list->count)--;
		
		next_node = next;
	}
	
	free_total += size;
	free(next_node->data);
	
	free_total += sizeof(next_node);
	free(next_node);
	
	(list->count)--;
	
	free_total += sizeof(struct list);
	free(list);
	
	return 0 ;
	
}

void printList(struct list * list)
{
	node * next = NULL;
	
	if(list == NULL)
		return ;
	
	node * next_node = list->head;
	
	if(next_node == NULL)
		return ;
	
	int temp = 0;
	while(next_node->next != NULL)
	{
		next = next_node->next;
		temp = * (int *)next_node->data;
		printf("%d\n",temp);
		next_node = next;
	}
	temp = * (int *)next_node->data;
	printf("%d\n",temp);
	
	return ;
}

struct list * createList()
{
	struct list * list = NULL;
	list = (struct list *) malloc(sizeof(struct list));
	malloc_total += sizeof(struct list);
	memset(list,0,sizeof(struct list));
	list->head = NULL;
	list->count = 0;
	return list ;
}


int main()
{
	struct list * list = NULL;
	list = createList();

	for(int i = 0; i < 1000; i++)
	{
		int * data = malloc(sizeof(int));
		malloc_total += sizeof(int);
		* data = i;
		insert(list,data);
	}
	
	printList(list);
	freeList(list,sizeof(int));
	printf("malloc total = %d \nfree total = %d \n",malloc_total,free_total);
	return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "7.h"

int malloc_size = 0;
int free_size = 0;
		
struct list * create_list()
{
	/*malloc the list*/
	struct list * list = NULL;
	list = (struct list * )malloc(list_size);	
	if(list == NULL)
		return NULL;
	malloc_size += list_size;
	memset(list,0,list_size);
	return list;
}	

int insert(struct list * list,int data)
{
	if(list == NULL)
		return -1;
	
	/*malloc the node */
	struct node * node = NULL;
	node = (struct node *)malloc(node_size);
	if(node == NULL)
		return -1;
	malloc_size += node_size;
	memset(node,0,node_size);
	node->data = data;	
	
	/*if it's the first node*/
	if(list->first == NULL)
	{
		/*set the value of node*/
		node->left = NULL;
		node->right = NULL;
		list->first = node;
		list->last = node;
	}
	/*if it's not the first node*/
	else
	{
		struct node * node_now = NULL;
		node_now = list->first;
		while(node_now->right != NULL)
		{
			node_now = node_now->right;
		}
		node_now->right = node;
		node->left = node_now;
		list->last = node;
	}
	
	list->count += 1;
	return 0;
}

int freeAll(struct list * list)
{
	int free_size = 0;
	struct node * node_now = NULL;
	struct node * node_next = NULL;
	
	if(list == NULL)
	{
		return 0;
	}
	
	if(list->first == NULL || list->count == 0)
	{
		free(list);
		return (free_size + list_size);
	}
	
	node_now = list->first;
	
	/*free all node from first*/
	while(node_now != NULL)
	{
		node_next = node_now->right;
		free(node_now);
		free_size += node_size;
		node_now = node_next;
		list->count -= 1;
		list->first = node_now;
	}
	
	/*free the list*/
	if(list->count == 0)
	{
		free(list);
		free_size += list_size;
	}
	else
		return -1;
	
	return free_size;
}

int main()
{
/* 	int b = 100;
	int * a = &b;
//	if use "a" rather than "*a" here ,
//	a warning will be generated.
//	at that time ,the result will be false.
	printf("%d \n" , *a); */
	
	struct list * list = NULL;
	list = create_list();
	if(list == NULL)
		return -1;
	
	for (int i = 0 ; i < 100 ; i++)
	{
		insert(list,i);
	}
	
	/*free the all nodes first , free the list then*/
	int ret = freeAll(list);
	if(ret == -1)
		return -1;
	else
		free_size += ret;
	
	printf("malloc:%10d\n",malloc_size);
	printf("free:  %10d\n",free_size);
	
	return 0;
}
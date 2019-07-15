#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int malloc_total = 0;
static int free_total = 0;

struct TreeNode{
	int data ;
	struct TreeNode * left;
	struct TreeNode * right;
};

typedef struct TreeNode Node;

typedef struct{
	Node * root;
}Tree;

void insert (Tree * tree , int value)
{
	Node * node = malloc(sizeof(Node));
	malloc_total += sizeof(Node);
	memset (node , 0 , sizeof(Node));
	node->data = value;
	
	if(tree->root == NULL)
	{	
		tree->root = node ;
	}
	else
	{
		Node * temp = tree->root;
		while(temp != NULL)
		{
			if(value < temp->data)
			{
				if(temp->left == NULL)
				{
					temp->left = node;
					return;
				}
				else
					temp = temp->left;
			}
			else
			{
				if(temp->right == NULL)
				{
					temp->right = node;
					return;
				}
				else
				{
					temp = temp->right;
				}
			}
		}
	}
}

void freeTreeNode(Node * node)
{
	if(node == NULL)
		return;
	
	Node * left = node->left;
	Node * right = node->right;
	
	free(node);
	free_total += sizeof(Node);
	node = NULL;
	
	freeTreeNode(left);
	freeTreeNode(right);
}

void inoder(Node * node)
{
	if(node == NULL)
		return;
	
	inoder(node->left);
	printf("%d.",node->data);
	inoder(node->right);
}

int main(int argc , char ** argv)
{
	Tree * tree = malloc(sizeof(Tree));
	malloc_total += sizeof(Tree);
	memset(tree , 0 ,sizeof(Tree));
	
	for(int i = 0; i < 10 ; i ++ )
	{
		insert(tree,i);
	}
	
	for(int i = -10; i < 0 ; i ++ )
	{
		insert(tree,i);
	}
	
	insert(tree , -11);
	insert(tree , 5);
	insert(tree , 5);
	
	inoder(tree->root);
	printf("\n");
	
	freeTreeNode(tree->root);
	free(tree);
	free_total += sizeof(Tree);
	
	printf("malloc total = %d , free total = %d\n",malloc_total , free_total);
	exit(0);
}
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

/*
	insert the small one in left ,
	insert the big one in right,
	no operation if value exist.
*/
void insert (Tree * tree , int value , Node * node)
{
	if(node == NULL)
	{
		node = malloc(sizeof(Node));
		malloc_total += sizeof(Node);
		memset (node , 0 , sizeof(Node));
		node->data = value;
	}
	else
	{
		node->left = NULL;
		node->right = NULL;
	}
	
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
			else if(value > temp->data)
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
			else
			{
				free(node);
				free_total += sizeof(Node);
				return;
			}
		}
	}
}

void insert_after_delete_node(Tree * tree, Node * node)
{
	if(tree == NULL || node == NULL)
		return;
	
	insert_after_delete_node(tree, node->left);
	insert_after_delete_node(tree, node->right);
	insert(tree, node->data , node);
}


/* delete the node which is specified */
void deleteNode( Tree * tree , int value)
{
	Node * node = tree->root;
	Node * father_node = node;
	
	while(node != NULL )
	{
		/*left is small*/
		if(value > node->data)
		{
			father_node = node;
			node = node->right;
		}
		/* right is big */
		else if(value < node->data)
		{
			father_node = node;
			node = node->left;
		}
		/* equal */
		else
		{
			Node * left_node = node->left;
			Node * right_node = node->right;
			
			/* no left node and right node , delete directly */
			if(!left_node && !right_node)
			{
				father_node->left == node ? (father_node->left = NULL) : (father_node->right = NULL);
				free(node);
				node = NULL;
				free_total += sizeof(Node);
			}	
			/* no left but right existed , copy right to this node , free the right */
			else if(!left_node && right_node)
			{
				memcpy(node , right_node ,sizeof(Node));
				free(right_node);
				node = NULL;
				free_total += sizeof(Node);
			}
			
			else if(left_node && !right_node)
			{
				memcpy(node , left_node ,sizeof(Node));
				free(left_node);
				node = NULL;
				free_total += sizeof(Node);
			}
			
			/* both existed */
			else
			{
				/*root node ,add left node to right */
				if(node == tree->root)
				{
					tree->root = right_node;
					
					free(node);
					node = NULL;
					free_total += sizeof(Node);
				
					insert_after_delete_node(tree,left_node);
					return;
				}
				/* no root node , move left and right to the tree */
				father_node->left == node ? (father_node->left = NULL) : (father_node->right = NULL);
				free(node);
				node = NULL;
				free_total += sizeof(Node);
				
				insert_after_delete_node(tree,left_node);
				insert_after_delete_node(tree,right_node);
			}
			/*
			if(node == tree->root)
			{
				Node * left_node = node->left;
				Node * right_node = node->right;
				tree->root = right_node;
				
				free(node);
				node = NULL;
				free_total += sizeof(Node);
				
				insert_after_delete_node(tree,left_node);
			}
			else
			{
				Node * left_node = node->left;
				Node * right_node = node->right;

				father_node->left == node ? (father_node->left = NULL) : (father_node->right = NULL);
				free(node);
				node = NULL;
				free_total += sizeof(Node);
					
				insert_after_delete_node(tree,left_node);
				insert_after_delete_node(tree,right_node);
			}
			*/
		}
	}
}

/* free all node on the tree */
void freeALLTreeNode(Node * node)
{
	if(node == NULL)
		return;
	
	Node * left = node->left;
	Node * right = node->right;
	
	free(node);
	free_total += sizeof(Node);
	node = NULL;
	
	freeALLTreeNode(left);
	freeALLTreeNode(right);
}

/* scan the tree */
void inoder(Node * node)
{
	if(node == NULL)
		return;
	
	inoder(node->left);
	printf("%d.",node->data);
	inoder(node->right);
}


/* get the tree depth */
int depth(Node * node)
{
	if(node == NULL)
		return 0;
	
	int leftmax = depth(node->left);
	int rightmax = depth(node->right);
	
	if(leftmax > rightmax)
		return leftmax + 1;
	else
		return rightmax + 1;
	
}

int main(int argc , char ** argv)
{
	Tree * tree = malloc(sizeof(Tree));
	malloc_total += sizeof(Tree);
	memset(tree , 0 ,sizeof(Tree));
	
	for(int i = 0; i < 15 ; i ++ )
	{
		insert(tree,i,NULL);
	}
	
	for(int i = -10; i < 0 ; i ++ )
	{
		insert(tree,i,NULL);
	}
	
	insert(tree , -11,NULL);
	//insert(tree , 5,NULL);
	//insert(tree , 5,NULL);
	
	
	inoder(tree->root);
	printf("\n");
	printf("depth of tree = %d\n",depth(tree->root));
	
	
	deleteNode(tree,0);
	inoder(tree->root);
	printf("\n");
	printf("depth of tree = %d\n",depth(tree->root));
	
	//deleteNode(tree,1);
	//deleteNode(tree,2);

	deleteNode(tree,-10);
	inoder(tree->root);
	printf("\n");
	printf("depth of tree = %d\n",depth(tree->root));
	
	
	freeALLTreeNode(tree->root);
	free(tree);
	free_total += sizeof(Tree);
	printf("malloc total = %d , free total = %d\n",malloc_total , free_total);
	exit(0);
}
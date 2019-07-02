#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int total_malloc = 0;
static int total_free = 0;

struct BTreeNode{
	int data;
	struct BTreeNode * left;
	struct BTreeNode * right;
};

int create_btree(struct BTreeNode ** bt)
{
	int val = 0;
	
	scanf("%d",&val);
	
	if(val == 0)
	{
		return 0;
	}
	
	*bt = malloc(sizeof(struct BTreeNode ));
	memset(*bt , 0 , sizeof(struct BTreeNode ));
	total_malloc += sizeof(struct BTreeNode );
	
	(*bt)->data = val;
	printf("%d->left:",val);
	create_btree(&((*bt)->left));
	printf("%d->right:",val);
	create_btree(&((*bt)->right));
}

void delete_tree_node(struct BTreeNode ** root)
{
	if( root == NULL || *root == NULL)
		return ;
	
	delete_tree_node(&(*root)->left);
	delete_tree_node(&(*root)->right);
	total_free += sizeof(struct BTreeNode);
	free(*root);
	*root = NULL;
}

void delete_tree(struct BTreeNode ** root)
{
	if( root == NULL )
		return ;
	
	total_free += sizeof(struct BTreeNode *);
	free(root);
	root = NULL;
}

void preOderTree(struct BTreeNode ** root)
{
	if(root == NULL || *root == NULL)
	{
		return ;
	}
	
	printf("%d,",(*root)->data);
	preOderTree(&(*root)->left);
	preOderTree(&(*root)->right);
	
}

void inOderTree(struct BTreeNode ** root)
{
	if(root == NULL || *root == NULL)
	{
		return ;
	}
	
	inOderTree(&(*root)->left);
	printf("%d,",(*root)->data);
	inOderTree(&(*root)->right);
	
}

void postOderTree(struct BTreeNode ** root)
{
	if(root == NULL || *root == NULL)
	{
		return ;
	}
	
	postOderTree(&(*root)->left);
	postOderTree(&(*root)->right);
	printf("%d,",(*root)->data);
	
}

int maxdepth(struct BTreeNode ** root)
{
	if(root == NULL || *root == NULL)
		return 0;
	
	int leftDepth  = maxdepth(&(*root)->left);
	int rigthDepth = maxdepth(&(*root)->right);
	
	if(leftDepth > rigthDepth)
		return leftDepth+1;
	else 
		return rigthDepth+1;
}


int main( int argc ,char ** argv)
{
	struct BTreeNode ** root = NULL;
	root = (struct BTreeNode **)malloc(sizeof(struct BTreeNode *));
	total_malloc += sizeof(struct BTreeNode *);
	create_btree(root);
	
	preOderTree(root);
	printf("\n");
	inOderTree(root);
	printf("\n");
	postOderTree(root);
	printf("\n");
	printf("tree depth = %d\n",maxdepth(root));

	delete_tree_node(root);
	delete_tree(root);
	printf("malloc=%d bytes, free=%d bytes\n",total_malloc,total_free);
	
	exit(0);
	
}
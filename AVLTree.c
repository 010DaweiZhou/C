#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AVLTree.h"

static int malloc_total ;
static int free_total ;

static 
avltree left_left_rotation(avltree tree)
{
	
	avlnode * k1 = tree->left;
	tree->left = k1->right;
	k1->right = tree;
	
	/* root ago */
	tree->height = MAX(get_node_height(tree->left) , get_node_height(tree->right)) + 1;
	/* root now */
	k1->height = MAX(get_node_height(k1->left) , get_node_height(k1->right)) + 1;
	
	return k1;
}


static 
avltree right_right_rotation(avltree tree)
{
	
	avlnode * k2 = tree->right;
	tree->right = k2->left;
	k2->left = tree;
	
	/* root ago */
	tree->height = MAX(get_node_height(tree->left) , get_node_height(tree->right)) + 1;
	/* root now */
	k2->height = MAX(get_node_height(k2->left) , get_node_height(k2->right)) + 1;
	
	return k2;
}

static
avltree left_right_rotation(avltree tree)
{
	tree->left = right_right_rotation(tree->left);
	tree = left_left_rotation(tree);
	return tree;
}

static
avltree right_left_rotation(avltree tree)
{
	tree->right = left_left_rotation(tree->right);
	tree = right_right_rotation(tree);
	return tree;
}

void in_order_avltree(avltree tree)
{
	if(tree == NULL)
		return ;
	
	in_order_avltree(tree->left);
	printf("%d.",tree->key);
	in_order_avltree(tree->right);
}


int get_node_height(avlnode * node)
{
	return HEIGHT(node);
}


avlnode * create_node(elementType key,avlnode * left , avlnode * right)
{
	avlnode * node = malloc(sizeof(avlnode));

	if(node == NULL)
		return NULL;
	
	malloc_total += sizeof(avlnode);
	
	memset(node,0,sizeof(avlnode));
	node->key = key;
	node->left = left;
	node->right = right;
	//node->height = 0;
	
	return node;
}

avltree avltree_insertNode(avltree tree , elementType key)
{
	/* empty tree */
	if(tree == NULL)
	{
		tree = create_node(key , NULL , NULL);
	}
	else if(tree->key < key)
	{
		/* insert right */
		tree->right = avltree_insertNode(tree->right , key);
		
		if(HEIGHT(tree->right) - HEIGHT(tree->left) == 2)
		{
			if(key > tree->right->key )
				tree = right_right_rotation(tree);
			else
				tree = right_left_rotation(tree);
		}
	}
	else if(tree->key > key)
	{
		/* insert left */
		tree->left = avltree_insertNode(tree->left , key);
		
		if(HEIGHT(tree->left) - HEIGHT(tree->right) == 2)
		{
			if(key < tree->left->key )
				tree = left_left_rotation(tree);
			else
				tree = left_right_rotation(tree);
		}
	}
	else
	{
		;
	}
	
	/* adjust the height of tree */
	tree->height = MAX(get_node_height(tree->left) , get_node_height(tree->right)) + 1;
	return tree;
}


avlnode * search_node(avltree tree , elementType key)
{
	if(tree == NULL || key == tree->key)
		return tree;
	
	/* parameter is bigger , find on right sub-tree*/
	if(tree->key < key)
		return search_node(tree->right,key);
	else 
		return search_node(tree->left,key);
	
}

void delete_tree(avlnode * root)
{
	if(root == NULL)
		return ;
	
	/* find the leaf node , free it first */
	delete_tree(root->left);
	delete_tree(root->right);
	
	free_total += sizeof(*root);
	free(root);
	root = NULL;
	
}

avltree 
avltree_deleteNode(avltree tree ,elementType key)
{
	
	
}

int main( int argc ,char ** argv)
{
	avlnode * node = NULL;
	avltree tree = avltree_insertNode(NULL , 6);
	
	tree = avltree_insertNode(tree , 3);
	tree = avltree_insertNode(tree , 9);
	tree = avltree_insertNode(tree , 5);
	tree = avltree_insertNode(tree , 2);
	tree = avltree_insertNode(tree , 4);
	tree = avltree_insertNode(tree , 11);
	tree = avltree_insertNode(tree , 8);
	tree = avltree_insertNode(tree , 1);
	tree = avltree_insertNode(tree , 7);
	
	in_order_avltree(tree);
	printf("\n");
	
	node = search_node(tree , 6);
	if(node != NULL)
	{
		printf("key = %d,height = %d\n",node->key,node->height);
	}
	
	delete_tree(tree);
	tree = NULL;
	
	printf("malloc_total = %d\n",malloc_total);
	printf("free_total = %d\n",free_total);
	
	exit(0);
}
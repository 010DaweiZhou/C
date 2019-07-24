#ifndef AVLTREE_H_INCLUDE
#define AVLTREE_H_INCLUDE

typedef int elementType;

typedef struct node{
	elementType key;
	struct node * left;
	struct node * right;
	int height;
}avlnode, *avltree;


#define HEIGHT(node) ((node == NULL) ? 0 : ((avlnode*)node)->height)
#define MAX(a,b) ((a)>(b) ? (a):(b))

int get_node_height(avlnode * node);

avlnode * create_node(elementType key,avlnode * left , avlnode * right);

avlnode * maximun_node (avltree tree);

avlnode * minimun_node (avltree tree);

void in_order_avltree(avltree tree);

avlnode * search_node(avltree tree , elementType key);

avltree avltree_insertNode(avltree tree , elementType key);

avltree avltree_deleteNode(avltree tree ,elementType key);

#endif
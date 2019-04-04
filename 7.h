

struct node
{
	struct node * left;
	int data;
	struct node * right;
};

struct list
{
	struct node * first;
	struct node * last;
	int count;
};

#define list_size sizeof(struct list)
#define node_size sizeof(struct node)


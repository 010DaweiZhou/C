
typedef struct listnode{
	void * data;
	struct listnode * next;
}node;


struct list{
	int count;
	node * head;
};
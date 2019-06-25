#ifndef SIMPLE_HASH

	#define SIMPLE_HASH
	#define HASH_SIZE 1024 * 1024

	static unsigned int malloc_total;
	static unsigned int free_total;

	struct student{
		char name[10];
		unsigned char age;
	};
		
	struct hash_node
	{
		void * data;
	};
	typedef struct hash_node HashNode;

	struct hash_table{
		HashNode ** table;
	};
	typedef struct hash_table HashTable;
#endif
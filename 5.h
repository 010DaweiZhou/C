

struct student
{
	char * name;
	char * address;
	unsigned char age;
};

union date{
	int day;
	char month[20];
	int year;
}a;

typedef unsigned int u32_t;
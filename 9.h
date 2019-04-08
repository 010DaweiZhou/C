

/*
	using for save memery
	total length showld be less than 8 bit
	it's different to using char and unchar
*/
typedef struct my_domain{
/* 	char a : 3;
	char b : 3;
	char c : 1; */
	
	unsigned char a : 3;
	unsigned char b : 3;
	unsigned char c : 2;
}domain;


#define ADD(x,y) x+y

#define MAX(a,b) (a>b)?a:b
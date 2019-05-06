#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


#define SIZE 1024

int main(int argc , char * argv[])
{
	char buf[SIZE] = {};
	
	/* print the kind , size of stdin buf first */
	if(stdin->_flags & _IO_UNBUFFERED)
		printf("unbuffered\n");
	else if(stdin->_flags & _IO_LINE_BUF)
		printf("line-buffered\n");
	else
		printf("fully-buffered\n");
	printf("buffer size :%ld\n", 
						stdin->_IO_buf_end - stdin->_IO_buf_base);
	
	/* set buf size and kind of stdin */
	if(setvbuf(stdin , buf , _IONBF , SIZE) != 0)
	{
		printf("set buf failed!\n");
		exit(1);
	}
	
	/* print the kind , size of stdin buf second */
	if(stdin->_flags & _IO_UNBUFFERED)
		printf("unbuffered\n");
	else if(stdin->_flags & _IO_LINE_BUF)
		printf("line-buffered\n");
	else
		printf("fully-buffered\n");
	printf("buffer size :%ld\n",
						stdin->_IO_buf_end - stdin->_IO_buf_base);
				
				
	/* print the kind , size of stdout buf*/
	if(stdout->_flags & _IO_UNBUFFERED)
		printf("unbuffered\n");
	else if(stdout->_flags & _IO_LINE_BUF)
		printf("line-buffered\n");
	else
		printf("fully-buffered\n");
	printf("buffer size :%ld\n\n", 
						stdout->_IO_buf_end - stdout->_IO_buf_base);
					
	
	if(argc != 2 || strlen(argv[1]) == 0)
	{
		printf("a filepath needed!\n");
		exit(1);
	}
	
	/* clean up context of file, can read write */
	FILE * file = fopen(argv[1],"w+");
	if(file ==NULL)
	{
		printf("open stream failed\n");
		exit(1);
	}
	fprintf(file , "hello it's linux C program!\n");
	fclose(file);
	
	
	/* read write */
	int fd = -1;
	if((fd = open(argv[1],O_RDWR)) == -1)
	{
		printf("file open failed!\n");
		exit(0);
	}
	
	
	/* open a stream based on fd */
	if((file = fdopen(fd,"a+")) == NULL)
	{
		printf("open stream failed!\n");
		exit(1);
	}
	fprintf(file , "It's the second write!\n");
	fclose(file);
	
	
	/* read char from stream */
	int get_char = 0;
	file = fopen(argv[1],"r");
	while((get_char = getc(file)) != EOF)
	{
		printf("%c",get_char);
	}
	fclose(file);
	printf("\n");
	
	
	/* read string from stream */
	char get_str[SIZE] = {};
	file = fopen(argv[1],"r");
	while(fgets(get_str , SIZE , file) == get_str)
	{
		printf("%s",get_str);
	}
	fclose(file);
	printf("\n");
	
	
	
	/* writye from direct I/O , append the file */
	char * data = "hello , I'm form fwrite\n";
	if(( file = fopen(argv[1],"a+")) == NULL)
		return -1;
	int write_num = strlen(data);
	fwrite(data , sizeof(char) , write_num , file);
	fclose(file);
	printf("write successful!\n\n");
	
	
	/* read from direct I/O */
	memset(buf , 0 , SIZE);
	if((file = fopen(argv[1],"r")) == NULL)
		return -1;
	int read_num ; 
	while((read_num = fread(buf , sizeof(char) , 1024 , file)) > 0)
	{
		printf("%s",buf);
	}
	fclose(file);
	printf("\n");
	
	
	return 0;
}
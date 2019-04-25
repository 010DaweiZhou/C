#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define FLAGS O_WRONLY|O_CREAT|O_TRUNC

int main(int argc , char * argv[])
{
/* 	if(stdin->_flags & _IO_UNBUFFERED)
		printf("unbuffered\n");
	else if(stdin->_flags & _IO_LINE_BUF)
		printf("line-buffered\n");
	else
		printf("fully-buffered\n");
	
	printf("buffer size :%ld\n",
				stdin->_IO_buf_end - stdin->_IO_buf_base);
*/
	if(argc != 2)
	{
		printf("a filename needed!\n");
		return -1;
	}
	
	char * param = argv[1];
	
	if(strlen(param) > 10)
	{
		printf("too long filename!\n");
		return -1;
	}

	int fd = open(param,FLAGS);
	if(fd = 0 )
	{
		printf("open file failed!\n");
		return -1;
	}
	
	printf("open file success!\n");
	
	
	int ret = close(fd);
	if(ret)
	{
		printf("close file failed!\n");
		return -1;
	}	
	
	return 0;
	
}
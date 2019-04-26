#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define FLAGS O_RDWR|O_APPEND|O_CREAT

typedef unsigned long uint64_t;

int main(int argc , char * argv[])
{
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
	if(fd == -1)
	{
		printf("open file failed!\n");
		return -1;
	}
	printf("open file success!\n");
	
	if(chmod(param,0666) == -1)
	{
		printf("chmod failed!\n");
		return -1;
	}
	
	off_t offset = lseek(fd, 0 , SEEK_CUR);
	printf("current offset:%ld\n",offset);
	
	char * buf = "hello world!\n";
	if(write(fd,buf,strlen(buf)) == -1)
	{
		printf("write failed!\n");
		return -1;
	}
	printf("%ld bytes written\n",strlen(buf));
	
	
	char read_buf[1024];
	memset ( read_buf , 0 ,1024);
	/* move p to start */
	lseek(fd , 0 , SEEK_SET);
	ssize_t read_bytes = 0;
	
	/* the preference of != is higher than =  , so () needed here */
	if((read_bytes = read(fd, read_buf ,1024)) != 0)
	{
		printf("%s",read_buf);
	}
	printf("%ld bytes readed!\n" , read_bytes);
	
	int ret = close(fd);
	if(ret)
	{
		printf("close file failed!\n");
		return -1;
	}	
	
	return 0;
	
}
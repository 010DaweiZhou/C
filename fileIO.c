#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>

#define ERR_EXIT(m)\
	do\
	{\
		perror(m);\
		exit(EXIT_FAILURE);\
	}\
	while(0)
	
	
#define BUFSIZE 4096
	
int main(int argc , char ** argv)
{
	int fd;
	int fd_w;
	char buf[BUFSIZE] = {0};
	int write_length = -1;
	int read_length = 0;
	int read_total = 0;
	int write_total = 0;
	
	
	if(!argv[1])
		ERR_EXIT("destination filepath needed!");
	
	/* open file */
	fd = open(argv[1], O_CREAT|O_RDWR|O_TRUNC , 0666);
	if(fd < 0)
		ERR_EXIT("open failed!");
	
	char * str = "hello world!\n";
	strcpy(buf , str);
	
	/*write and get time of write*/
	int i = 0;
	unsigned long start = time(NULL);
	for( i = 0; i < 1000000 ; i++)
	{
		write_length = write(fd , buf , strlen(str));
		if(write_length != strlen(str))
			ERR_EXIT("write failed!");

	}
	unsigned long end = time(NULL);
	
	printf("%lu sec cost!\n",end - start);
	close(fd);
	
	/* create a big file */
	
	
	
	/* copy from STDIN to STDOUT */
/*	
	while((read_length = read(STDIN_FILENO , buf , BUFSIZE)) > 0)
	{
		ret = write(STDOUT_FILENO , buf , read_length);
		if(ret != read_length )
			ERR_EXIT("write failed ");
	}
	
	printf("\ncopy successful!\n");
*/
	
	
	
/*	
	fd = open("file",O_RDWR|O_CREAT|O_TRUNC,0666);
	
	if(fd < 0 )
		ERR_EXIT("create error!");
	
	//read to file
	char * str = "hello world!\n";
	strcpy(buf, str);
	write(fd , buf , strlen(str));
	lseek(fd, 20 , SEEK_END);
	write(fd , buf , strlen(str));
	
	
	//read to buf
	lseek(fd , 0 , SEEK_SET);
	memset(buf , 0 , BUFSIZE);
	read_length = read(fd , buf , BUFSIZE);
	
	printf("bytes read = %u\n" , read_length);
	printf("buf:%s" , buf);
	
	close(fd);
*/	
	exit(0);
}
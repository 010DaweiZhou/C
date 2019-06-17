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
	
	int write_length = 0;
	int read_length = 0;
	
	int read_total = 0;
	int write_total = 0;
	
	/* copy file to destination */
	if(!argv[1] || !argv[2])
		ERR_EXIT("filepath needed!\n");
	
	/* get read and write fd */
	fd = open(argv[1] , O_RDWR|O_CREAT , 0666);
	fd_w = open(argv[2] , O_TRUNC|O_RDWR|O_CREAT , 0666);
	
	if(fd < 0 || fd_w < 0)
		ERR_EXIT("Open error!\n");
	
	/* 
		write to file  after read from file .
		read_length equal 0 when get the end of file.
	
	*/
	while((read_length = read(fd , buf , BUFSIZE)) > 0)
	{
		read_total += read_length;
		write_length = write(fd_w , buf , read_length);
		write_total += write_length;
		memset(buf , 0 , BUFSIZE);
		if(write_length != read_length )
			ERR_EXIT("write error!\n");
	}
	
	printf("read %d bytes ,write %d bytes \n",read_total , write_total);
	close(fd);
	close(fd_w);
	exit(0);
}
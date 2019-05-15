#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <time.h>

int main(int argc , char * argv[])
{
	mode_t mode = 0666;
	if(argc != 2)
		exit(1);
	
	if(mkfifo(argv[1],mode) < 0)
		exit(1);
	
	else
		printf("success !\n");
	
	int id = 0;
	
	if((id = fork()) < 0)
	{
		exit(1);
	}
	else if(id == 0)
	{
		int fd = 0;
		if((fd = open(argv[1],O_WRONLY)) < 0)
			exit(1);
		
		for(int i = 0; i < 10; i++)
		{
			char write_buf[PIPE_BUF];
			memset(write_buf, 0, PIPE_BUF);
			time_t tp ;
			time(&tp);
			int n = sprintf(write_buf,"%s",ctime(&tp));
			printf("write:%s",write_buf);
			
			if((write(fd, write_buf, n+1) < 0))
				exit(1);
			sleep(1);
		}
		
		close(fd);
	}
	else
	{
		int fd = 0;
		char read_buf[PIPE_BUF];
		memset(read_buf, 0, PIPE_BUF);

		if((fd = open(argv[1],O_RDONLY)) < 0)
		{
			printf("open fifo failed!\n");
			exit(1);
		}
		int len  = 0;
		while((len = read(fd, read_buf, PIPE_BUF)) > 0)
		{
			printf("read:%s",read_buf);
			memset(read_buf, 0, PIPE_BUF);
		}
		close(fd);
		exit(0);
	}
	unlink(argv[1]);
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>

#define BUFSIZE 512

int main(int argc , char ** argv)
{
	int socket_id = -1;
	int ret = -1;
	int size = 0;
	char buf[BUFSIZE] = {};
	
	socket_id = socket(AF_INET, SOCK_DGRAM, 0);
	if(socket_id < 0 )
	{
		exit(1);
	}
	size = sizeof(struct sockaddr_in);
	printf("socket id = %d\n",socket_id);
	
	
	struct sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("192.168.100.200");
	addr.sin_port = htons(10588);
	
	while(1)
	{	  
		memset(buf, 0 , BUFSIZE);
		fgets(buf, BUFSIZE, stdin);
		sendto(socket_id , buf, BUFSIZE , 0 , 
			  (struct sockaddr*)&addr, size);
	}
	
	close(socket_id);
	exit(0);
}
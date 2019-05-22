#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#define PORT 10225
#define BUFSIZE 255

int main(int argc , char ** argv)
{
	int sockfd = -1 ;
	int new_socket_id = -1;
	char buf[BUFSIZE] = {};
	uint32_t addr_len = sizeof(struct sockaddr_in);
	struct sockaddr_in addr ;
	
	memset(&addr, 0, sizeof(struct sockaddr_in));
	
	/* create a new socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(sockfd < 0)
		exit(1);
	
	printf("socket create successsful! %u\n",sockfd);
	
	/* server properties */
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr("192.168.100.200");
	
	/* bind the socket to a port */
	if(bind(sockfd, (struct sockaddr *)&addr , addr_len) < 0)
	{
		perror("bind");	
		exit(1);
	}	
	printf("bind port successful!port = %d\n",PORT);	
	
	/* listen the port */
	if(listen( sockfd , 10) < 0 )
		exit(1);
	
	printf("listen socket successful!\n");
	printf("listening...\n");
	
	while(1)
	{
		/* accept the new connect of the port and return a new socket */
		new_socket_id = accept(sockfd, (struct sockaddr *)&addr, &addr_len);
		
		if(new_socket_id < 0)
		{
			exit(1);
		}
		printf("connect successful! new socket id = %u\n",new_socket_id);
		
		char * str = "hello , here is server!";
		strcpy(buf , str);
		
		size_t size = write(new_socket_id, buf, sizeof(buf));
		memset(buf , 0 , BUFSIZE);
		size = read(new_socket_id , buf , BUFSIZE);
		printf("%s\n",buf);
		// send(new_socket_id, buf , sizeof(buf) , 0);
		// memset(buf ,0 ,sizeof(buf));
		// recv(new_socket_id , buf, sizeof(buf) , 0);
		// printf("%s\n",buf);
		
		close(new_socket_id);
	}
	
	/* close sockets at last */
	close(sockfd);
	
	exit(0);
}
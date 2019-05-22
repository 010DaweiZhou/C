#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUFSIZE 255

int main(int argc , char ** argv)
{
	int sockfd = -1 ;
	int ret = -1;
	char buf[BUFSIZE] = {};
	struct sockaddr_in addr;
	
	memset(&addr ,0 ,sizeof(struct sockaddr));
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(10225);
	/* here can't use htonl() */
	addr.sin_addr.s_addr = inet_addr("192.168.100.200");
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("create socket successful! sockfd = %d\n",sockfd);
	
	if(sockfd < 0)
		exit(1);
	
	ret = connect(sockfd , (struct sockaddr *)&addr , sizeof(struct sockaddr));
	if(ret < 0)
		exit(1);
	
	printf("connect successful!\n");
	
	size_t size = read(sockfd, buf , BUFSIZE);
	printf("%s\n",buf);
	memset(buf , 0 , BUFSIZE);
	strcpy(buf,"hello , here is client!");
	size = write(sockfd , buf, BUFSIZE);
	
	/* send and receive */
	// recv( sockfd, buf, sizeof(buf), 0);
	// printf("%s\n",buf);
	// strcpy(buf , "hello,here is client!");
	// send(sockfd ,buf ,sizeof(buf), 0);
	
	close(sockfd);
	
	exit(0);
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc , char ** argv)
{
	struct hostent * host_ip;
	struct in_addr addr = {};
	char * addr_str = NULL;
	uint32_t * addr1 = NULL;
	
	if(argv[1] == NULL)
	{
		printf("please input a parameter!\n");
		exit(1);
	}
	
	host_ip = gethostbyname(argv[1]);
	
	if(host_ip == NULL)
	{
		printf("bad parameter!\n");
		exit(1);
	}
	
	addr1 =  (uint32_t *)host_ip->h_addr_list[0];
	
	if(addr1 != NULL)
	{
		printf("addr = %d\n", *addr1 );
	}
	else
	{
		printf("get addr failed!\n");
		exit(1);
	}
	

	addr.s_addr =  (*addr1);
	addr_str = inet_ntoa(addr);
	
	if(addr_str == NULL)
	{
		printf("cast to ip failed!\n");
	}
	
	printf("ip address = %s\n",addr_str);
	return 0;
}
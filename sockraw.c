#include <stdio.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <stdlib.h>
#include <netdb.h>
#include <setjmp.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define PACKET_SIZE 4096
#define MAX_WAIT_TIME 3
#define MAX_NO_PACKETS 5

int datalen = 56;
int nsend = 0, nreceive = 0;
int socket_id = -1;
char sendpacket[PACKET_SIZE];
char recvpacket[PACKET_SIZE];
struct sockaddr_in dest_addr;
struct sockaddr_in source_addr;
struct timeval tvrecv;

/* call back function of alarm for timeout */	
void statistics(int signal)
{
	if(nsend != 0)
		printf("%d packet send , %d packet receive , %%%d lost\n",
				nsend , nreceive , 
				(nsend - nreceive)/nsend * 100);
	close(socket_id);
	exit(1);
}

/* create socket raw for icmp */
int creat_socket()
{
	struct protoent * protocol = NULL;

	protocol = getprotobyname("icmp");
	
	if(protocol == NULL)
	{
		exit(1);
	}
	
	socket_id = socket(AF_INET , SOCK_RAW , protocol->p_proto);
	
	if(socket_id < 0)
	{
		exit(1);
	}
	return socket_id;
}

/* caculate the check sum for packet */
unsigned short check_sum(unsigned short * addr , int len)
{
	unsigned int sum = 0;
	
	while(len > 1)
	{
		sum += *addr++;
		len -= 2;
	}
	
	if(len == 1)
	{
		sum += *(unsigned char *)addr;
	}	
	
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >>16);
	return (~sum);

}

/* pack the packet */
int pack(int packet_number)
{
	struct icmp * icmp;
	struct timeval * val;
	int packet_size = 0;
	
	icmp = (struct icmp *) sendpacket;
	icmp->icmp_type = ICMP_ECHO;
	icmp->icmp_code = 0;
	icmp->icmp_cksum = 0;
	icmp->icmp_seq = packet_number;
	icmp->icmp_id = getpid();
	/* with ip header */
	packet_size = 8 + datalen;
	val = (struct timeval *)icmp->icmp_data;
	gettimeofday(val, NULL);
	icmp->icmp_cksum = check_sum((unsigned short *)icmp , packet_size);
	return packet_size;
}

/* send packet to destination */
void send_packet(char * argv)
{
	int i = 0;
	int ret = 0;
	int packet_size = 0;
	printf("-----------------------Ping-----------------------\n");
	for(i = 1 ; i < MAX_NO_PACKETS ; i++)
	{
		packet_size = pack(i);
		/* the packet size is ip_hr + icmp_hr + data */
		ret = sendto(socket_id, sendpacket,packet_size,0,
				(struct sockaddr *)&dest_addr,sizeof(dest_addr));
				
		if(ret < 0)
		{
			perror("error");
			exit(1);
		}
		
		printf("PING %s(%s) %d bytes data in ICMP packets.\n"
				,argv,inet_ntoa(dest_addr.sin_addr),datalen);
		/* use for statistics*/
		nsend++;
		sleep(1);
	}
}

/* unpack the packet , len is recvfrom's return value*/
int unpack(char * buf, int len)
{
	struct ip * ip = NULL;
	struct timeval * tvsend ;
	double rtt = 0;
	
	/*icmp an ip packet */
	ip = (struct ip *)buf;
	
	/* ??? */
	int iphdrlen = ip->ip_hl << 2;
	
	/* get icmp packet */
	struct icmp * icmp = (struct icmp *)(buf + iphdrlen);
	
	/* get the length of icmp */
	len -= iphdrlen;
	
	if(len < 8)
	{
		printf("bad receive!\n");
		return -1;
	}
	
	if(icmp->icmp_type == ICMP_ECHOREPLY && icmp->icmp_id == getpid())
	{
		/* get the time i send to remote */
		tvsend = (struct timeval*)icmp->icmp_data;
		int sec = tvrecv.tv_sec - tvsend->tv_sec ;
		int usec = tvrecv.tv_usec - tvsend->tv_usec ;
		
		/* 
			caculte the time interval , 
			here must use 1000.0 ,
			otherwise you will get xxx.000,
			icmp->icmp_seq = 1,2,3,4,5...
		*/
		rtt = sec * 1000 + usec / 1000.0 - 
				(MAX_NO_PACKETS - icmp->icmp_seq) * 1000;
		
		printf("%d bytes from %s:icmp_seq=%d ttl=%d time=%.3fms \n",
			len , inet_ntoa(source_addr.sin_addr), icmp->icmp_seq,
			ip->ip_ttl, rtt);
			
		nreceive ++;
	}
	else
	{
		return -1;
	}
}

void receive_packet()
{
	int fromlen;
	int n = 0;
	/* signal for time out */
	signal(SIGALRM,statistics);
	
	fromlen = sizeof(source_addr);
	
	while(nreceive < nsend)
	{
		/*replace the old one*/
		alarm(MAX_WAIT_TIME);
		n = recvfrom(socket_id, recvpacket, sizeof(recvpacket), 0,
					(struct sockaddr *)&source_addr, &fromlen);
		
		if(n < 0)
		{
			perror("error:");
			continue;
		}
		/* get now time */
		gettimeofday(&tvrecv, NULL);
		
		if(-1 != unpack(recvpacket,n))
			continue;
		
	}
}


void set_param(char * argv)
{
	int size = 50 * 1024;
	struct hostent * host ;
	unsigned long inaddr = 0;
	
	/* set the socket's status , here set the L3's buf size */	
	setsockopt(socket_id,SOL_SOCKET,SO_RCVBUF,&size,sizeof(size));
	
	/* set the destnation */	
	dest_addr.sin_family = AF_INET;
	
	/* change the parameter to ip address if it's necessary */
	if((inaddr = inet_addr(argv)) == INADDR_NONE)
	{
		host = gethostbyname(argv);
		if(host == NULL)
		{
			printf("Bad hostname!\n");
			exit(1);
		}
		memcpy(&dest_addr.sin_addr, host->h_addr, host->h_length);
	}
	else
	{
		/* copy ip address directly */
		memcpy(&dest_addr.sin_addr, &inaddr, 4);
	}
}

int main(int argc , char ** argv)
{
	/* destination address from parameter */
	if(argv[1] == NULL)
	{
		printf("a parameter needed!\n");
		exit(1);
	}
	/* get socket raw for icmp */
	socket_id = creat_socket();

	memset(&dest_addr , 0 ,sizeof(struct sockaddr));
	memset(&source_addr , 0 ,sizeof(struct sockaddr));
	
	/* set the destination */
	set_param(argv[1]);
	
	/* send icmp echo packet */
	send_packet(argv[1]);
	
	/* receive ipcm echo replay */
	receive_packet();
	
	printf("%d packet send , %d packet receive , %%%d lost\n",
			nsend , nreceive , 
			(nsend - nreceive)/nsend * 100);
			
	close(socket_id);
	
	exit(0);
}
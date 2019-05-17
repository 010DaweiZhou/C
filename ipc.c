#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>

struct msg_buf
{
	long mtype;
	char mtext[255];
};

/*
	In my pc .
　　cat /proc/sys/kernel/msgmax       8k	每个消息的最大长度
　　cat /proc/sys/kernel/msgmnb       16k   每个消息队列的总的字节数
　　cat /proc/sys/kernel/msgmni       32000 系统上消息队列的总数
*/
void msg_stat(int msgid, struct msqid_ds msg_info)
{
	msgctl(msgid, IPC_STAT , &msg_info);
	printf("current number of bytes:%ld\n",msg_info.msg_cbytes);
	printf("number of message:%ld\n",msg_info.msg_qnum);
	printf("max bytes on queue:%ld\n",msg_info.msg_qbytes);
}

int main(int argc, char * argv[])
{
	key_t key = 0;
	int ret = 0;
	int msgid = 0;
	struct msg_buf buf = {};
	struct msqid_ds msg_info = {};
	int msgtype = getpid();
	
	/* get a key of pathname*/
	key = ftok("./generic.h",1);
	printf("key = %d , msgtype = %d\n", key, msgtype);
	
	/* get msqid */
	msgid = msgget(key , IPC_CREAT|IPC_EXCL|0666);
	printf("msgid = %d \n" ,msgid);
	
	buf.mtype = msgtype;
	strcpy(buf.mtext, "hello world!");
	
	/* use the queue to send message */
	ret = msgsnd(msgid, &buf, sizeof(buf.mtext), IPC_NOWAIT);
	printf("send ret = %d\n",ret);
	
	sleep(1);
	
	
	msg_stat(msgid, msg_info);
	memset(&buf, 0, sizeof(struct msg_buf));
	
	/* use the queue to receive message */
	ret = msgrcv(msgid , &buf , sizeof(buf.mtext), msgtype, IPC_NOWAIT);
	printf("receive ret = %d\n",ret);
	
	printf("%s", buf.mtext);
	printf("\n");
	
	/* delete the queue */
	msgctl(msgid,IPC_RMID,NULL);
	
	return 0;
}
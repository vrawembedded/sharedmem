#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf
{
long mtype;
char mtext[10];
};



int main()
{
key_t key1, key2;
int mid,qid;
struct msgbuf msg;
msg.mtype= 1;
sprintf(msg.mtext, "%s", "varsha");

printf("begin:%s\n", __FILE__);
mid= msgget(key1, IPC_CREAT);

if(mid==-1)
{
perror("msgget");
}
else
{
printf("msgq created\n");
printf("mid: %d\n",mid);
}

if(qid=msgget(key2, IPC_CREAT)==-1)
{
perror("msgget2");
}
else
printf("msgq2 created\n");

if(msgsnd(mid, &msg, sizeof(msg.mtext), IPC_NOWAIT)==-1)
{
perror("msgsnd\n");
}
else
printf("msgsend succeed  %s\n", msg.mtext);

if(msgrcv(qid, &msg, sizeof(msg.mtext),2, IPC_NOWAIT)==-1)
{
perror("msgrcv\n");
}
else
{
printf("msgrcv received\n");
printf("msg received: %s\n",msg.mtext);
}
printf("end:%s\n", __FILE__);
return 0;
}
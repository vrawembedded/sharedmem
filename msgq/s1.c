#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

struct msgbuf
{
long mtype;
char text[10];
};

int main()
{
key_t key1, key2;
struct msgbuf msgs,ms;
int mid1,qid;

msgs.mtype=2;
sprintf(msgs.text, "%s","rawat");

printf("begin:%s\n",__FILE__);

mid1= msgget(key1, IPC_CREAT);
if(mid1==-1)
{
perror("msgget\n");
exit(EXIT_FAILURE);
}
else
printf("msgget success\n");

if(qid= msgget(key2, IPC_CREAT)==-1)
{
perror("msgq2");
}
else
{
printf("msgq2 created\n");
}
while(1)
{
if(msgrcv(qid, &ms, sizeof(ms.text),1,IPC_NOWAIT)==-1)
{
perror("msgrcv\n");
}
else
{
printf("msg received : %s\n",ms.text);
}

if(msgsnd(mid1, &msgs, sizeof(msgs.text), IPC_NOWAIT)==-1)
{
perror("msgsnd\n");
}
else
{
printf("msg send: %s\n", msgs.text);
}
}


printf("end:%s\n",__FILE__);

return 0;
}
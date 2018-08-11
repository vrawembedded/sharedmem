#include <stdio.h>
#include<fcntl.h>
#include <unistd.h>

int main()
{
int fd[2], ret;
pid_t pid;
char buff[5];
printf("begin:%s pid: %d\n",__func__,getpid());
printf("pid:%d  ppid: %d\n",getpid(), getppid());
ret= pipe(fd);
if(ret>0)
{
printf("pipe created\n");
}
else
perror("pipe");

ret= write(fd[1],"pipe",4);
if(ret<0)
{
perror("write");
}
else
printf("write done\n");

ret= fork();

if(ret==0)
{
printf("child created\n");

printf("pid:%d  ppid: %d\n",getpid(), getppid());
ret= read(fd[0],&buff,5);
if(ret>0)
{
printf("read done , buff= %s\n",buff);
}
else
perror("read");

}

sleep(1);
printf("end:%s\n",__func__);
return 0;
}
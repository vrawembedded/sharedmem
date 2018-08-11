#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
int fd1;
int ret;
char buff[5];
printf("begin : %s\n", __func__);
ret= mkfifo("./testfifo1",0666);
if(ret==-1)
{
perror("mkfifo");
}
else
printf("fifo created\n");

if((fd1= open("./testfifo1",O_RDONLY))<0)
{
perror("open");
}
else
printf("file open\n");

if((ret=read(fd1, &buff, 5))>0)
{
printf("read done, buff= %s\n",buff);
}
else
perror("read");

close(fd1);


printf("end : %s\n", __func__);
return 0;
}
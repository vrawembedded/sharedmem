#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

//#define fifo1 "/tmp/fifo1"
int main()
{
int  fd;
int ret;
//ar *fifo1= "/tmp/ff";
printf("begin : %s\n", __func__);
if((ret=mkfifo("./testfifo1",0666))<0)
{
perror("fifo");
}
else
printf("fifo created\n");

if((fd= open("./testfifo1",O_WRONLY))<0)
{
perror("open");
}
else
printf("file open\n");

if((ret= write(fd, "FIFO", 4))>0)
{
printf("write successfully\n");
}
else
perror("write");


close(fd);


printf("end : %s\n", __func__);
return 0;
}
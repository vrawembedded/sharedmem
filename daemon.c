#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <syslog.h>
#include <string.h>

void daemonize();

void daemonize()
{
printf("begin:%s\n",__FILE__);
pid_t pid, sid;
int i, fd;

pid= fork();   //// create child process

 if(pid>0)
{
printf("child created\n");
exit(0);    //// kill parent process
}

/*
if(getppid()==1)
{
printf("daemon starts\n");
}
*/

printf("%d\n",getppid());
umask(000);  /// set file permissions

sid=setsid();  /// make child process to session leader of process group
 
if(sid>0)
{
printf("session created\n");
}

//i= getdtablesize();
for(i=getdtablesize(); i>=0;--i)  /// close all standard I/O  descriptors ( stdin, stdout, stderr)
{
close(i);
}

fd = open("dev/null",O_RDWR);

if(fd !=-1)
{
dup(fd);
dup(fd);
}

chdir("/tmp/");   //// change directory

printf("end: %s\n", __FILE__);

}

int main()
{
//printf("begin:%s\n", __FILE__);
int ret,sock, i,j;
char message[1000] , server_reply[2000];
struct sockaddr_in client_address;
setlogmask(LOG_UPTO(LOG_INFO));
openlog("daemon starts",LOG_CONS|LOG_PERROR, LOG_USER);
syslog(LOG_INFO,"Daemon starting up");

daemonize();
syslog(LOG_INFO, "daemon running");

printf("%d\n",getppid());

sock= socket(AF_INET,SOCK_STREAM,0);
if(sock==-1)
{
perror("socket");
}
else
{
printf("socket created/n");
}

client_address.sin_addr.s_addr = inet_addr("127.0.0.1");
client_address.sin_family = AF_INET;
client_address.sin_port =  htons(32010);

if(connect(sock,(struct sock_addr)&client_address,sizeof(client_address))<0)
{
perror("connect");
}
else
{
puts("connect successfully");
}


 //keep communicating with server
    while(1)
//    for(i=0;i<10;i++)
    {
         sprintf(message,"@LIVE,357207051057453,XYZ,C,11/01/2018,15:56:54,2830.34567,N,07704.56789,E,0.0,0.00,0,0,0,4.0,SW_V1.2,1,99-%d",sock);
        //Send some data
        if( send(sock ,message ,strlen(message) , 0) < 0)
        {
            puts("Send failed");
//            return 1;
        }


        puts("Server reply :");
        puts(server_reply);
//       close(sock);
    }


         close(sock);
}

printf("end:%s\n", __FILE__);
return(0);
}









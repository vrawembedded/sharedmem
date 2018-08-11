#include <stdio.h>
#include <signal.h>
#include <unistd.h>


void sig_handler(int signo)
{
if(signo==SIGINT)
{
printf("SIGINT received");
}
}

int main()
{
struct sigaction sg;
sg.sa_handler= sig_handler;
printf("begin : %s\n",__FILE__);

if(signal(SIGINT, sig_handler)== SIG_ERR)
{
perror("signal");
}

sigaction(SIGINT, &sg,NULL);

while(1)
{
printf("no sig received\n");
sleep(1);
}



printf("end : %s\n",__FILE__);
return 0;
}



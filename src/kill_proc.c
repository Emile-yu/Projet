#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<signal.h>
void sig_hand(int sig)
{
	printf("signal recu [%d]\n",sig);
}
int main(int argc,char **argv)
{	
	if(argc != 2)
	{	
		printf("argc\n");
		exit(1);
	}
	sigset_t sig_proc;
	struct sigaction action;
	sigemptyset(&sig_proc);
	
	action.sa_mask=sig_proc;
	action.sa_flags=0;
	action.sa_handler=sig_hand;
	sigaction(SIGUSR1,&action,NULL);

	sigaddset(&sig_proc,SIGUSR1);
	sigprocmask(SIG_SETMASK,&sig_proc,NULL);

	int i,j,status;
	status=0;
	int N=atoi(argv[1]);
	int *pid;
	int init;
	int val;
	init=getpid();
	pid=(int *)malloc(N+1);
	pid[0]=init;
	for(i=0;i<N;i++)
	{	
		if(fork()==0)
		{
			pid[i+1]=getpid();
			if(i==N-1)
			{
				printf("Je suis dernier pid [%d]\n",getpid());
				val=(int)(rand () /(((double) RAND_MAX +1) /100));
				printf("val=%d\n",val);
				printf("Affichage des pid\n");
				for(j=0;j<=N;j++)
				{
					printf("Processus -->[%d],Pid -->[%d]\n",j,pid[j]);
				}
				
				kill(pid[N-1],SIGUSR1);				
				exit(0);
			}
		}
		else
		{	
			sigfillset(&sig_proc);
			sigdelset(&sig_proc,SIGUSR1);
			sigsuspend(&sig_proc);
			if(getpid()!=init)
			{
				printf("Processus [%d],Pid [%d],PPid [%d]\n",i,getpid(),getppid());
				/*exit(WEXITSTATUS(status));*/
				kill(pid[i-1],SIGUSR1);	
				exit(0);
			}
			else
			{
				printf("Processus Initial [0], Pid[%d]\n",getpid());
				/*printf("Valeur aleatoire %d\n",WEXITSTATUS(status));*/
				exit(0);
			}
			
		}
	}
	return EXIT_SUCCESS;
}

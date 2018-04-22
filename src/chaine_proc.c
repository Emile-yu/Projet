#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

int main(int argc,char **argv)
{	
	if(argc != 2)
	{	
		printf("argc\n");
		exit(1);
	}
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
	{	pid[i+1]=getpid();
		if(fork()==0)
		{
			
			if(i==N-1)
			{
				printf("Je suis dernier pid [%d]\n",getpid());
				val=(int)(rand () /(((double) RAND_MAX +1) /100));
				printf("val=%d\n",val);
				printf("Affichage des pid\n");
				for(j=0;j<N+1;j++)
				{
					printf("Processus -->[%d],Pid -->[%d]\n",j,pid[j]);
				}
				
				
				exit(val);
			}
		}
		else
		{
			wait(&status);
			WIFEXITED(status);
			if(getpid()!=init)
			{
				printf("Processus [%d],Pid [%d],PPid [%d]\n",i,getpid(),getppid());
				exit(WEXITSTATUS(status));	
			}
			else
			{
				printf("Processus Initial [0], Pid[%d]\n",getpid());
				printf("Valeur aleatoire %d\n",WEXITSTATUS(status));
				exit(0);
			}
			
		}
	}
	return EXIT_SUCCESS;
}

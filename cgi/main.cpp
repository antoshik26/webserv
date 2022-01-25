#include<iostream>
#include<sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h> 
# include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char **argv, char **env)
{
	/*pid_t		pid;
	int *ptr(0);
	char * const * nll = NULL;
	env[i]=new char[strlen(body["a"])];
	env[i]=(char *)body["a"];
	i++;
	env[i]=new char[strlen(body["b"])];
	env[i]=(char *)body["b"];
	int fd=open("tmp",O_WRONLY | O_TRUNC | O_CREAT, 0777 );
	pid = fork();

	if (!pid)
	{
		dup2(fd,1);

		execve("test.py",nll,env);
		std::cout<<"error: smt wrong execve"<<std::endl;
	}
	else
	{
		std::cout<<"error: smt wrong wt fork()"<<std::endl;
	}
	close(fd);
	return(0);*/
	int i=0;
	while(env[i])
	{
		std::cout<<env[i++]<<std::endl;
	}
}
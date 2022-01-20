#include<iostream>
#include<sys/types.h>
#include<unistd.h>
#include<string>
#include<stdlib.h>
void test(const char *_script,char **_env,int	*_pipe1, int	*_pipe2, int	fd1)
{
	pid_t	pid;

	if (!pid)
	{
		//pipe connect
		if (&pipe != 0)
		{
			dup2(_pipe1[1], 1);
			close(_pipe1[1]);
			close(_pipe1[0]);
		}
		if (&pipe != 0)
		{
			dup2(_pipe2[0], 0);
			close(_pipe2[1]);
			close(_pipe2[0]);
		}
		//redirect
		if (fd1 && !_pipe1)
		{
			dup2(fd1, 1);
			close(fd1);
		}
		else if (fd1 == -1 && !_pipe2)
		{
			dup2(1, 0);
			close(fd1);
		}
		else if (fd1 == -100 && !_pipe2)
			exit(0);//error handler need improvment
		else if (fd1 && !_pipe2)
		{
			dup2(fd1, 0);
			close(fd1);
		}
		if (access(_script,1) || execve(_script,0,_env))
		{
			std::cout<<"error while execve"<<std::endl;
		}
	}
	if (_pipe1 != 0)
	{
		close(_pipe1[1]);
		close(_pipe1[0]);
	}
}
int main(int argc, char **argv, char **env)
{
	int i;
	
	i = 0;
	while(argv[i]!=0)
	{
		i++;		
	}
	std::cout<<i<<std::endl;

}

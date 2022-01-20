#include"cgi.hpp"

cgi::cgi(std::string extension,std::map<std::string, std::map<std::string, std::string> > cgi,std::map<std::string, std::string> body,const char **env):_script(find_script(extension,cgi))
{
	this->fill_env(env,body);
	this->execve_script();
}

void cgi::execve_script()
{
	pid_t	pid;
	int pipe[2];

	
}
/*pid_t cgi::fork(int	*pipe_1, int	*pipe_2, int	fd1)
{
	pid_t	pid;

	if (!pid)
	{
		//pipe connect
		if (pipe != 0)
		{
			dup2(_pipe1[1], 1);
			close(_pipe1[1]);
			close(_pipe1[0]);
		}
		if (pipe != 0)
		{
			dup2(_pipe2[0], 0);
			close(_pipe2[1]);
			close(_pipe2[0]);
		}
		//redirect
		if (fd1 && !pipe_1)
		{
			dup2(fd1, 1);
			close(fd1);
		}
		else if (fd1 == -1 && !pipe_2)
		{
			dup2(1, 0);
			close(fd1);
		}
		else if (fd1 == -100 && !pipe_2)
			exit(0);//error handler need improvment
		else if (fd1 && !pipe_2)
		{
			dup2(fd1, 0);
			close(fd1);
		}
		if (access(_script,1) || execve(_script,0,_env))
		{
			std::cout<<"error while execve"<<std::endl;
		}
	}
	if (pipe_1 != 0)
	{
		close(pipe_1[1]);
		close(pipe_1[0]);
	}
}*/
#include"cgi.hpp"

cgi::cgi(std::string script, std::string *env):_script(script.c_str()){
	
	_env=env;//преобразовать string в char!!!!!!
	int		**pipe;
	int		i;
	pid_t	*pid;
	int		num;

	i = 0;
	num = size - 4;
	pipe = make_pipe(size - 4);
	pid = malloc(sizeof(pid) * (size - 3));
	if (!pid)
		return ;
	pid[i] = test(all[num--], pipe[i], pipe[i + 1], fd[1]);
	i++;
	while (0 < num)
	{
		pid[i] = test(all[num--], pipe[i], pipe[i + 1], 0);
		i++;
	}
	pid[i] = test(all[num--], pipe[i], pipe[i + 1], fd[0]);
	print_errors(pid, all, i);
	free_pipe(pipe, pid);

}
pid_t cgi::fork(int	*pipe_1, int	*pipe_2, int	fd1)
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
}
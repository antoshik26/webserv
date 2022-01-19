#ifndef CGI_HPP
#define CGI_HPP
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

class cgi
{
	private:
		int _pipe1[2];
		int _pipe2[2];

		const char* _script;
		const char* _env;
		pid_t fork(int	*pipe_1, int	*pipe_2, int	fd1);

	public:
	
		cgi(std::string _script, std::string *env)
		{
			_argv_cgi = argv_cgi;
			_env = env;
			// pipe[0] = 0;
			// pipe[1] = 1;
		}

		~cgi()
		{
			
		}

		// int cgi_challenge()
		// {
		// 	pipe(_pipe);
		// 	if (_pid = 0)
		// 	{
		// 		_pid = fork()
		// 	}
		// 	else
		// 	{
		// 		error = execve()
		// 		if (error != 0)
		// 		{
		// 			// throw;
		// 		}
		// 	}
		// 	return (error);
		// }
};
#endif
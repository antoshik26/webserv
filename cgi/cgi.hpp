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
		int _pipe[2];
		// pid_t _pid;
		std::string* _argv_cgi;
		std::string* _env;

	public:
		cgi()
		{
			_pipe[0] = 0;
			_pipe[1] = 1;
		}

		cgi(std::string *argv_cgi, std::string *env)
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
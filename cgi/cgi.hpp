#ifndef CGI_HPP
#define CGI_HPP
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "../config_parser/config_parser.hpp"
#include"../request_manager/request_manager.hpp"
class cgi
{
	private:
		const char* _script;
		char **_env;
		void fill_env(const char **env,	std::map<std::string, std::string> body);
		void fill_varibles(int i,	std::map<std::string, std::string> body);
		const char *find_script(std::string extension,std::map<std::string, std::map<std::string, std::string> > cgi);
		void execve_script();
		//pid_t fork(int	*pipe_1, int	*pipe_2, int	fd1);//?????????????? execve argv=[s]
	public:
	
		cgi(std::string extension,std::map<std::string, std::map<std::string, std::string> > cgi, std::map<std::string, std::string> body, const char **env);
		~cgi();
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
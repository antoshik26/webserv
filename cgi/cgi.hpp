#ifndef CGI_HPP
#define CGI_HPP
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <fstream>

#include "../config_parser/config_parser.hpp"
#include"../request_manager/request_manager.hpp"
class cgi
{
	private:
		char* _script;
		char **_env;
		void fill_env(const char **env,	std::map<std::string, std::string> body);
		void fill_varibles(int i,	std::map<std::string, std::string> body);
		const char *find_script(std::string extension,std::map<std::string, std::map<std::string, std::string> > cgi);
		void execve_script();
	public:
		cgi(const char **env);
		void new_cgi(std::string extension,std::map<std::string, std::map<std::string, std::string> > cgi,std::map<std::string, std::string> body);
		std::string get_string();
		virtual ~cgi();
};
#endif
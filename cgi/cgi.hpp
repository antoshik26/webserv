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
		int pos;
		int pipe1[2];
		void fill_env(char **env);
		void fill_varibles(std::map<std::string, std::string> body);
		void find_script(std::string extension,std::map<std::string, std::map<std::string, std::string> > cgi);
		void execve_script(std::string path);
	public:
		cgi();
		cgi(char **env);
		// void new_cgi(std::string extension, std::map<std::string, std::map<std::string, std::string> > cgi,std::map<std::string, std::string> body);//final
		// void new_cgi(std::map<std::string, std::string> body);//final
		void new_cgi(std::string path, std::map<std::string, std::string> body);//comment
		std::string get_string();
		~cgi();
};
#endif
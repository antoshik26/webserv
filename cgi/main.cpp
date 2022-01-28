#include<iostream>
#include<sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h> 
# include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include"cgi.hpp"

int main(int argc, char **argv, char **env)
{
	cgi c(env);
	std::map<std::string, std::string> m;
m["a"]="hello";
	m["b"]="world";
	c.new_cgi(m);
	std::cout<<"1 test:"<<c.get_string()<<std::endl;

	std::map<std::string, std::string> mw;

	mw["a"]="ggg";
	mw["b"]="efvgg";
	c.new_cgi(mw);
	std::cout<<"2 test:"<<c.get_string()<<std::endl;

	
}
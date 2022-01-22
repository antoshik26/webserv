#include"cgi.hpp"

cgi::cgi(std::string extension,std::map<std::string, std::map<std::string, std::string> > cgi,std::map<std::string, std::string> body,const char **env):_script(find_script(extension,cgi))
{
	this->fill_env(env,body);
	this->execve_script();
	file("tmp.txt");
}

void cgi::execve_script()
{
	pid_t	pid;
	int pipe[2];
	char * const * nll = NULL;

	pid=fork();
	if(pid==0)
	{
		execve(script,);
		std::cout<<"Eror: mistake while execve"<<std::endl;
	}
	else
	{
		std::cout<<"Eror: mistake while execve"<<std::endl;
	}
}

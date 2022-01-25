#include"cgi.hpp"

cgi::cgi(const char **env):_script()
{
	this->fill_env(env,body);
}
void cgi::new_cgi(std::string extension,std::map<std::string, std::map<std::string, std::string> > cgi,std::map<std::string, std::string> body)
{
	_script=find_script(extension,cgi);
	this->execve_script();

}
void cgi::execve_script()
{
	pid_t		pid;
	char * const * nll = NULL;
	int fd=open("tmp",O_WRONLY | O_TRUNC | O_CREAT, 0777 );
	pid = fork();

	if (!pid)
	{
		dup2(fd,1);
		execve("test.py",nll,this->env);
		std::cout<<"error: smt wrong execve"<<std::endl;
	}
	close(fd);

}

std::string get_string()
{
	std::string line;
	std::ifstream in("tmp");
	getline(in,line);
	in.close();
	return(line);
}

cgi::~cgi()
{

}
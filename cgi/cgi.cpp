#include"cgi.hpp"

cgi::cgi(char **env)
{
	this->fill_env(env);
}
//void cgi::new_cgi(std::string extension,std::map<std::string, std::map<std::string, std::string> > cgi,std::map<std::string, std::string> body)//final
void cgi::new_cgi(std::map<std::string, std::string> body) //comment
{
	int i=0;
	fill_varibles(body);
	//find_script(extension,cgi); final 
	/*while(_env[i])
	{
		std::cout<<_env[i++]<<std::endl; for test 
	}*/
	this->execve_script();
	delete _env[pos];
	delete _env[pos+1];
}
void cgi::execve_script()
{
	pid_t		pid;
	char * const * nll = NULL;
	int fd=open("tmp",O_TRUNC |O_WRONLY| O_CREAT, 0777 );
	pid = fork();
	int f;
	if (!pid)
	{
		dup2(fd,1);
		execve("test.py",nll,this->_env);
		std::cout<<"error: smt wrong execve"<<std::endl;
	}
	wait(&f);
	close(fd);
}

std::string cgi::get_string()
{
	std::string line;
	std::ifstream in("tmp");
	getline(in,line);
	in.close();
	return(line);
}

cgi::~cgi()
{
	int i;

	i = 0;
	//while(i<pos)
	//{
		//delete _env[i++];
		//std::cout<<_env[i++]<<std::endl; draft
	//}
//	delete _env[i+2];
	delete [] _env;
	//delete _script;
}
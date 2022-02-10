#include"cgi.hpp"

cgi::cgi()
{}

cgi::cgi(char **env)
{
	this->fill_env(env);
}
void cgi::new_cgi(std::string extension,std::map<std::string, std::map<std::string, std::string> > cgi,std::map<std::string, std::string> body)//final
//void cgi::new_cgi(std::map<std::string, std::string> body) //comment
{
	fill_varibles(body);
	find_script(extension,cgi); //final 
	/*while(_env[i])
	{
		std::cout<<_env[i++]<<std::endl; for test 
	}*/
	this->execve_script();
	// delete _env[pos];
	// delete _env[pos+1];
}
void cgi::execve_script()
{
	pid_t		pid;
	char * const * nll = NULL;
	if(pipe(pipe1))
	{
		std::cout<<"error: pipe"<<std::endl;
	}
	pid = fork();
	int f;
	if (!pid)
	{ 
		dup2(pipe1[1],1);
		close(pipe1[1]);
		_script = "./web_document/7000_port/scripts/test.py";
		execve(_script,nll,this->_env);
		std::cout<<"error: smt wrong execve"<<std::endl;
	}
	wait(&f);
	close(pipe1[1]);
}

std::string cgi::get_string()
{
	FILE *stream;
    int c;
	std::string ans;
    stream = fdopen (pipe1[0], "r");
    while ((c = fgetc (stream)) != EOF)
    {   
		ans.push_back(c);
	}
    fclose (stream);
	return(ans);
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
	// delete [] _env;
	//delete _script;
}


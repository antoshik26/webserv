#include"cgi.hpp"

cgi::cgi()
{
	pos=0;
}

cgi::cgi(char **env)
{
	this->fill_env(env);
}
// void cgi::new_cgi(std::string extension,std::map<std::string, std::map<std::string, std::string> > cgi,std::map<std::string, std::string> body)//final
void cgi::new_cgi(std::string script,std::map<std::string, std::string> body) 
{
	fill_varibles(body);
	//find_script(extension,cgi); //comment 
	// this->execve_script();
	this->execve_script(script);

	delete _env[pos];
	delete _env[pos+1];
	//delete _script; depeends on args comment?
}
void cgi::execve_script(std::string script)
// void cgi::execve_script()
{
	pid_t		pid;
	char * const * nll = NULL;
	if(pipe(pipe1))
	{
		std::cout<<"error: pipe"<<std::endl;
	}
	std::cout << script << std::endl;
	pid = fork();
	int f;
	if (!pid)
	{ 
		dup2(pipe1[1],1);
		close(pipe1[1]);
		// _script = "./web_document/7000_port/scripts/test.py";
		execve(script.c_str(),nll,this->_env);
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
	if (pos==0)
		return;
	while(_env[i])
	{
	//	delete _env[i];
		i++;
	}
	//delete[] _env[i+2];
	//delete [] _env;
	//delete _script;
}


#include"cgi.hpp"

void cgi::fill_env(char **env)
{
	int i;
	
	i = 0;
	while(env[i]!=0)
		i++;
	this->_env=new char*[i+3];
	this->_env[i+2]=0;
	this->pos=i;
	_env[pos]=0;
	_env[pos+1]=0;
	while (i>0)
	{
		i--;
		this->_env[i]=new char[strlen(env[i])];
		this->_env[i]=(char *)env[i];
	}
}

void cgi::fill_varibles(std::map<std::string, std::string> body)
{
	this->_env[pos]=new char[body["a"].length()+2];
	strcpy(this->_env[pos],("a="+body["a"]).c_str());
	this->_env[pos+1]=new char[body["b"].length()+2];
	strcpy(this->_env[pos+1],("b="+body["b"]).c_str());
}

void cgi::find_script(std::string extension, std::map<std::string, std::map<std::string, std::string> > cgi)
{
	std::string search;
	search = cgi.find(".py")->first;
	this->_script=new char[ cgi.find(".py")->first.length()];
	strcpy(_script,search.c_str()); 
}
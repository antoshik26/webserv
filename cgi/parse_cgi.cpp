#include"cgi.hpp"

void cgi::fill_env(const char **env,	std::map<std::string, std::string> body)
{
	int i;
	
	i = 0;
	while(env[i]!=0)
		i++;
	this->_env=new char*[i+3];
	this->_env[i+2]=0;
	fill_varibles(i,body);
	while (i>0)
	{
		i--;
		this->_env[i]=new char[strlen(env[i])];
		this->_env[i]=(char *)env[i];
	}
}
void cgi::fill_varibles(int i,	std::map<std::string, std::string> body)
{
	this->env[i]=new char[strlen(body["a"])+2];
	this->env[i]="a="(char *)body["a"];
	i++;
	this->env[i]=new char[strlen(body["b"])+2];
	this->env[i]="b="+(char *)body["b"];
}

const char *cgi::find_script(std::string extension, std::map<std::string, std::map<std::string, std::string> > cgi)
{
	std::string search;
	search = cgi.find(".py")->first;
	return((char*)search.c_str());
}
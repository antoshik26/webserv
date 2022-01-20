#include"cgi.hpp"

void cgi::fill_env(const char **env,	std::map<std::string, std::string> body)
{
	int i;
	
	i = 0;
	while(env[i]!=0)
		i++;
	this->_env=new char*[i+2];
	this->_env[i+1]=0;
	fill_varibles(i,body);
	//his->_env[i]="QUERRY_ARRAY=A:III?B:IIII";//DRAFT
	while (i>0)
	{
		i--;
		this->_env[i]=new char[strlen(env[i])];
		this->_env[i]=(char *)env[i];
	}
}
void cgi::fill_varibles(int i,	std::map<std::string, std::string> body)
{
	//body[];
}
const char *cgi::find_script(std::string extension, std::map<std::string, std::map<std::string, std::string> > cgi)
{
	std::string search;
	search = cgi.find(".py")->first;
	return(search.c_str());
}
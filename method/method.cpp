#include "method.hpp"
method ::method()
{
	fill();
	parse_body();
	parse_headers();
}
void method::fill()
{
	int i;
	
	i=0;
	/*body*/
	try
	{
		while(i<size_headers)
		{
			headers[all_headers[i++]]="";
		}
	}
	catch()
	{
		std::cout<<"error"<<std::endl;
	}
}

/*parse*/

int method::parse_body()
{
	int i;

	i=0;
	std::getline(std::cin,name,32);
	if(std::find(names.begin(),names.end(),name))
	{
		return ERROR;
	}
	std:getline(std::cin,path);
	if (path.find("HTTP 1.1")!=std::string::npos)
	{
		path.erase(path.find("HTTP 1.1"), path.end());// доп проверки
	}
	else
	{
		return ERROR;
	}
	

}

int method::parse_headers()
{
	
}
/*methods*/
void method::methodDelete()
{
    
}
void method::methodGet()
{
	
}
void method::methodPost()
{
    
}

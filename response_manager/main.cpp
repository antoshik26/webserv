#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include"iostream"
#include"string"
int Exists(const char *path)
{
    struct stat info;

    if(stat( path, &info ) != 0)
        return 0;
    else 
        return 1;
}

int main(int argc, char **argv)
{
	std::string result="testo123";
	std::string fi="test";
	if(result.find(fi)==0)
	{
		result.erase(result.begin(),result.begin()+fi.length());
	}
    return 0;
}
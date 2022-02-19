#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <fstream>
int main(int main,char **argv,char **env)
{
    char * const * nll = NULL;
    execve("script.sh",nll,env);
}
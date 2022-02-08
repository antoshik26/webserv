#include "./serv/serv.hpp"
#include "./client/client.hpp"
#include "./config_parser/config_parser.hpp"
#include "./request_manager/request_manager.hpp"
#include "./Cookies/cookies.hpp"
#include "./cgi/cgi.hpp"
#include <fstream>


int  main(int argc, char* argv[], char* env[])
{
	(void)argc;
	(void)argv;
	(void)env;
	std::ifstream fs;
	std::string line;
	std::string config;
	int error = 0;
	size_t i = 0;
	size_t j = 0;
	argv[1] = "config.conf";
	cgi cgi_scripst(env);
	std::vector<config_parser> list_conf;
	
	try
	{
		fs.open(argv[1]);
		if (fs.is_open())
		{
			while (getline(fs, line))
			{
				config = config + line + '\n';
				line.clear();
			}
		}
		else
		{
			// throw;
		}
		while ((i = config.find("server", i)) != std::string::npos)
		{
			if (j == 0)
			{
				i = i + 7;
				j = i;
			}
			else
			{
				line = config.substr(j, i - j);
				list_conf.push_back(config_parser(line));
				i = i + 7;
				j = i;
			}
		}
		line = config.substr(j, i - config.length());
		list_conf.push_back(config_parser(line));
		cookies cookies_serv(list_conf);
		serv myserv(list_conf, cookies_serv, cgi_scripst);
	}
	catch (std::exception &e)
	{
		// return(error);
	}
	return (0);
}

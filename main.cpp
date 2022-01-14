#include "./serv/serv.hpp"
#include "./client/client.hpp"
#include "./config_parser/config_parser.hpp"
#include "./request_manager/request_manager.hpp"
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
	std::vector<config_parser> list_conf;
	try
	{
		fs.open(argv[1]);
		if (fs.is_open())
		{
			while (getline(fs, line))
			{
				std::cout << line << std::endl;
				config = config + line;
				line.clear();
			}
		}
		else
			// throw;
		while (i == config.find("server"))
		{
			if (j == 0)
			{
				i = j;
			}
			else
			{
				line = config.substr(j, i - j);
				list_conf.push_back(config_parser(line));
			}
		}
		config_parser config(argv[1]);
		serv myserv(config);
		// int client_socket_fd;
		client cl;


		error = myserv.serv_bind();
		// if (error != 0)
		// 	throw;
		
		// if (error != 0)
		// 	throw;
		error = myserv.listen_fd();
		// error = myserv.accept_serv(cl.get_config());
		// client_socket_fd = myserv.accept_serv();
		myserv.new_client(); //select, poll, kqueue
		

		// while (true)
		// {
		// 	// size_t length = 1;
		// 	int i = 1;
		// 	int j = -1;
		// 	char ptr[4096];

		// 	// while (i > 0)
		// 	// {
		// 	i = recv(client_socket_fd, ptr, 4096, 0);
		// 	j++;
		// 	// }
		// 	if (i > 0)
		// 	{
		// 		std::cout << std::string(ptr, 0, i) << std::endl;
		// 		break;
		// 	}
		// }
	}
	catch (std::exception &e)
	{
		// return(error);
	}
	return (0);
}

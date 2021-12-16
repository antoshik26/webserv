#include "./serv/serv.hpp"
#include "./client/client.hpp"
#include "./config_parser/config_parser.hpp"
#include "./request_manager/request_manager.hpp"


int  main(int argc, char* argv[], char* env[])
{
	(void)argc;
	(void)argv;
	(void)env;
	int error = 0;
	try
	{
		config_parser config;
		serv myserv(config);
		int client_socket_fd;
		client cl;


		error = myserv.serv_bind();
		// if (error != 0)
		// 	throw;
		
		// if (error != 0)
		// 	throw;
		error = myserv.listen_fd();
		// error = myserv.accept_serv(cl.get_config());
		client_socket_fd = myserv.accept_serv();
		while (true)
		{
			// size_t length = 1;
			int i = 1;
			int j = -1;
			char ptr[4096];

			// while (i > 0)
			// {
			i = recv(client_socket_fd, ptr, 4096, 0);
			j++;
			// }
			if (i > 0)
				std::cout << std::string(ptr, 0, i) << std::endl;
		}
	}
	catch (std::exception &e)
	{
		// return(error);
	}
	return (0);
}

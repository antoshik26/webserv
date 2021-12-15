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
		client cl;


		error = myserv.serv_bind();
		// if (error != 0)
		// 	throw;
		error = myserv.accept_serv(cl.get_config());
		// if (error != 0)
		// 	throw;
		// cl.connect_client



	}
	catch (std::exception &e)
	{
		// return(error);
	}
	return (0);
}

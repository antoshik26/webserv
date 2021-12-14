#ifndef SERV_HPP
#define SERV_HPP
#include <iostream>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include "../cofig_parser/config_parser.hpp"

#define		serv_port 5000; //считывать с config		 
#define		fd_count 500;

// typedef struct in_addr
// {
// 	in_addr_t s_addr;
// };

// typedef struct sockaddr_in
// {
// 	uint8_t sa_len;
// 	sa_famaly_t sa_family;
// 	in_port_t sin_port;
// 	struct in_addr sin_addr;
// 	char sin_zero[8];
// }; //ipv4

// sockaddr_in6 ipv6

// struct sockaddr_in = {
// 	.sin_famaly = AF_INET;
// 	.sin_addr.s_addr = INADDR_ANY;
// 	.sin_port = htons(serv_port);
// }

class serv
{
	private:
		// char* env[];
		sockaddr_in *serv_config;
		int socket_fd;
		// std::string buf;
		char buf[1024];
		// sockaddr_in6 serv_config_ipv6;
		// hostent ip_adress_connect;

	public:
		serv()
		{

		}

		serv(const Config_parser conf_serv)
		{
			try
			{
				int error = 0;
				(void)conf_serv;
				// serv_config.sin_len = 
				serv_config->sin_family = AF_INET;
				// serv_config.sin_port = htons(conf_serv.get_listen_port);
				serv_config->sin_addr.s_addr = INADDR_ANY;
				// serv_config.sin_addr.s_addr = inet_addr("127.0.0.1"); на приватный ip адресс
				socket_fd = socket(AF_INET, SOCK_STREAM, 0);
				error =  bind(socket_fd, (sockaddr *)serv_config, (socklen_t)(sizeof(serv_config)));
				
				error = listen_fd(); 
			}
			catch(std::exception &e)
			{
				throw;
			}
		}

		serv(serv &obj)
		{
			(void)obj;
		}

		serv operator=(serv &obj)
		{
			(void)obj;
			return (*this);
		}
		
		~serv()
		{
			// close(socket_fd);
		}

		int reading()
		{
			int count_read = 0;

			// int count_read = recv(socket_fd, buf, 1024, 1);
			count_read = send(socket_fd, buf, 1024, 1);
			// count_read = read(socket_fd, buf, 1024);
			
			return (count_read);
		}

	private:
		int listen_fd()
		{
			int error = 0;
			
			error = listen(socket_fd, 5);
			return (error);
		}
};

#endif
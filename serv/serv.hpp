#ifndef SERV_HPP
#define SERV_HPP
#include <iostream>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdio.h>

#include "../config_parser/config_parser.hpp"

#define		serv_port		5000; //считывать с config		 
#define		fd_count		500;
#define		fd_setsize		256;
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
		sockaddr_in serv_config;
		int socket_fd;
		// std::string buf;
		char buf[1024];
		fs_set multithreaded_fd;
		// sockaddr_in6 serv_config_ipv6;
		// hostent ip_adress_connect;

	public:
		serv()
		{

		}

		serv(const config_parser conf_serv)
		{
			try
			{
				// int error = 0;
				(void)conf_serv;
				bzero((char *) &serv_config, sizeof(serv_config));
				// serv_config.sin_len = 
				serv_config.sin_family = AF_INET;
				// serv_config.sin_port = htons(conf_serv.get_listen_port);
				serv_config.sin_addr.s_addr = INADDR_ANY;
				// serv_config.sin_addr.s_addr = inet_addr("127.0.0.1"); на приватный ip адресс
				socket_fd = socket(AF_INET, SOCK_STREAM, 0);
				// error =  bind(socket_fd, (sockaddr *)serv_config, (socklen_t)(sizeof(serv_config)));
				// error = listen_fd(); 
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
			close(socket_fd);
		}
		
		// int setsockopt()
		// {

		// }

		// int getsockopt()
		// {

		// }

		int serv_bind()
		{
			int error = 0;
			try
			{
				error =  bind(socket_fd, (sockaddr *)&serv_config, (socklen_t)(sizeof(serv_config)));
				if (error != 0)
				{
					// throw;
				}
				// else
				// 	_fd_sockfd = sockfd; 
			}
			catch(std::exception &e)
			{
				// throw;
			}
			return (error);
			
		}

		int reading()
		{
			int count_read = 0;

			// int count_read = recv(socket_fd, buf, 1024, 1);
			count_read = send(socket_fd, buf, 1024, 1);
			// count_read = read(socket_fd, buf, 1024);
			
			return (count_read);
		}

		int accept_serv(const sockaddr_in* client_config)
		{
			int sock_klient = 0;
			try
			{
				sock_klient = accept(socket_fd, (sockaddr *)&client_config, (socklen_t*)(sizeof(client_config)));
				if (sock_klient < 0)
				{
					// throw;
				}
				// else
				// 	_fd_sockfd = sockfd; 
			}
			catch(std::exception &e)
			{
				// throw;
			}
			return (sock_klient);
		}
		
		int listen_fd()
		{
			int error = 0;
			
			error = listen(socket_fd, 5);
			return (error);
		}

		int select()
		{
			FD_ZERO(&multithreaded_fd);

			return (fd_new_client);
		}
};

#endif
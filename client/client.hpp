#ifndef CLIENT_HPP
#define CLIENT_HPP
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


class client
{
	private:
		int _fd_sockfd;
		char buf[1024];
		sockaddr_in client_config;
	public:
		client()
		{
			bzero((char *) &client_config, sizeof(client_config));
			client_config.sin_family = AF_UNIX;
			client_config.sin_addr.s_addr = INADDR_ANY;
			bzero(buf, 1024);
			_fd_sockfd = socket(AF_INET, SOCK_STREAM, 0);
		}

		client(int fd_sockfd)
		{
			bzero(buf, 1024);
			_fd_sockfd = fd_sockfd;
			client_config.sin_family = AF_INET;
			client_config.sin_addr.s_addr = INADDR_ANY;

		}

		client(const client &obj)
		{
			(void)obj;	
		}

		client operator=(const client &obj)
		{
			(void)obj;
			return (*this);
		}
		
		~client()
		{
			close(_fd_sockfd);
		}

		sockaddr_in* get_config()
		{
			return (&client_config);
		}
			
		// void send_info_in_socet()
		// {
		// 	// send
		// }

		// int connect_client(int sockfd, sockaddr_in *obj)
		// {
		// 	int error = 0;
		// 	try
		// 	{
		// 		error = accept(sockfd, (sockaddr *)obj, (socklen_t*)(sizeof(obj)));
		// 		if (error != 0)
		// 		{
		// 			// throw;
		// 		}
		// 		else
		// 			_fd_sockfd = sockfd; 
		// 	}
		// 	catch(std::exception &e)
		// 	{
		// 		// throw;
		// 	}
		// 	return (error);
		// }

		int connect_client(int sockfd, sockaddr_in *obj)
		{
			int error = 0;
			try
			{
				error = connect(sockfd, (sockaddr *)obj, (sizeof(obj)));
				if (error != 0)
				{
					// throw;
				}
				else
					_fd_sockfd = sockfd; 
			}
			catch(std::exception &e)
			{
				throw;
			}
			return (error);
		}

		void get_sock(int fd_sockfd)
		{
			_fd_sockfd = fd_sockfd;
		}

		int put_request() //post get delete запросы
		{
			int count_read2;
			count_read2 = send(_fd_sockfd, buf, 1024, 0);
			return (1);
		}
};

#endif
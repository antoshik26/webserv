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
#include <sys/poll.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <dirent.h>
// #include <sys/epoll.h>
#include <sys/event.h>
#include <sys/stat.h>

#include "../config_parser/config_parser.hpp"
#include "../request_manager/request_manager.hpp"
#include "../cgi/cgi.hpp"

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
		// std::map<int, stasd> multiserv;
		// typedef struct serv
		// {
		// 	sockaddr_in serv_config
		// 	int socket_fd;
		// 	poll;
		// }	
		sockaddr_in serv_config;
		int socket_fd;
		int count_serv;
		// kqueue
		// int kqueuefd;
		// struct kevent kevent_struct;
		// poll
		// struct pollfd fds[200];
		// select


		int client_socket_fd;
		pollfd poll_server_client_socketfd[10];	//плохо
		// std::vector<pollfd> fds();			//хорошо
		int count_client;						//отвратительно
		// std::pair<int, int> pull_server_client_socketfd[100];
		// request_manager request;


	public:
		serv()
		{

		}

		serv(const config_parser conf_serv)
		{
			try
			{
				count_serv = 1;
				count_client = 0;
				int option = 1;
				int ret = 0;
				// int error = 0;
				(void)conf_serv;
				bzero((char *) &serv_config, sizeof(serv_config));
				// serv_config.sin_len = 
				serv_config.sin_family = AF_INET;
				serv_config.sin_port = htons(8000);
				// serv_config.sin_port = htons(conf_serv.get_listen_port);
				serv_config.sin_addr.s_addr = INADDR_ANY;
				bzero(serv_config.sin_zero, 8);
				// serv_config.sin_addr.s_addr = inet_addr("127.0.0.1"); на приватный ip адресс
				socket_fd = socket(AF_INET, SOCK_STREAM, 0);
				ret = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&option, sizeof(option));
				ret = fcntl(socket_fd, F_SETFL, O_NONBLOCK);
				// error =  bind(socket_fd, (sockaddr *)serv_config, (socklen_t)(sizeof(serv_config)));
				// error = listen_fd(); 
				// epull();
				for (int i = 0; i < 10; i++)
				{
					poll_server_client_socketfd[i].fd = -1;
					poll_server_client_socketfd[i].events = 0;
					poll_server_client_socketfd[i].revents = 0;
				}
				poll_server_client_socketfd[0].fd = socket_fd;
				poll_server_client_socketfd[0].events = POLLIN;
				// poll_server_client_socketfd[0].fd = socket_fd;
				// poll_server_client_socketfd[0].events = POLLIN;
				// ret = fcntl( listen_fd, F_SETFL, O_NONBLOCK );
			}
			catch(std::exception &e)
			{
				throw;
			}
		}

		int get_sock()
		{
			return (socket_fd);
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

		int accept_serv(int socket_serv)
		{
			int sock_klient = 0;
			try
			{
				sock_klient = accept(socket_serv, NULL, NULL);
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
			
			error = listen(socket_fd, 32);
			return (error);
		}

		int add_client_in_poll(int socket_serv)
		{
			int new_client = 0;

			if ((new_client = accept_serv(socket_serv)) == -1)
			{
				// throw;
				return (new_client);
			}
			else
			{
				count_client++;
				poll_server_client_socketfd[count_client].fd = new_client;
				poll_server_client_socketfd[count_client].events = POLLIN;
				return (1);
			}
			return (0);
		}

		int new_client()
		{
			// int new_client = -1;
			int i;
			int rc;
			int rc2;
			char buffer[5024];
			int error;
			std::string a;
			bzero(buffer, 5024);

			try
			{
				while (true)
				{
					rc2 = poll(poll_server_client_socketfd, 10, -1);
					i = 0;
					while (rc2 > 0 && i < 10)
					{
						if (poll_server_client_socketfd[i].revents == 0)
						{
							i++;
							continue;
						}
						if (i < count_serv)
						{
							error = add_client_in_poll(poll_server_client_socketfd[i].fd);
							if (error == 1)
								rc2--;
						}
						else
						{

							rc = recv(poll_server_client_socketfd[i].fd, buffer, 5024, 0);
							std::cout << "aaaaaaaa " << poll_server_client_socketfd[i].fd << std::endl;
							printf("%s\n", buffer);
							char b[] = "HTTP/1.1 200 OK\r\n\r\n Hello World \r\n\r\n";
							rc = send(poll_server_client_socketfd[i].fd, b, strlen(b), 0); //бред
							close(poll_server_client_socketfd[i].fd);
							poll_server_client_socketfd[i].fd = -1;
							rc2--;
							bzero(buffer, 5024);
						}
						i++;
					}
					// while(i < count_client)
					// {
					// 	rc = recv(poll_server_client_socketfd[i].fd, buffer, 5024, 0);
					// 	if (rc < 0)
					// 	{
					// 		// throw;
					// 	}
					// 	else
					// 	{
					// 		if (rc > 0)
					// 		{
					// 			// std::cout << std::string(buffer, 0, rc) << std::endl;
					// 			std::cout << "aaaaaaaa " << poll_server_client_socketfd[i].fd << std::endl;
					// 			printf("%s\n", buffer);
					// 		}
					// 		// 	break;
					// 		char b[] = "HTTP/1.1 200 OK\r\n\r\n asdfgh \r\n\r\n";
					// 		// a = "asdfghjmmnbvdsa";
					// 		rc = send(poll_server_client_socketfd[i].fd, b, strlen(b), 0); //бред

					// 	}
					// 	i++;
					// 	bzero(buffer, 5024);
					// }

					// size_t length = 1;
					// int i = 1;
					// int j = -1;
					// char ptr[4096];

					// while (i > 0)
					// {
					// i = recv(client_socket_fd, ptr, 4096, 0);
					// j++;
					// // }
					// if (i > 0)
					// {
					// 	std::cout << std::string(ptr, 0, i) << std::endl;
					// 	break;
					// }
					// request.save_request(ptr);
				}
				// connect();
				// answer();
			}
			catch(std::exception &e)
			{
				// throw;
			}
		
			return (0);
		}		

		int connect()
		{
			int i;

			i = 0;
			while (i < 100)
			{
				if (poll_server_client_socketfd[i].fd == -1)
					break;
				i++;
			}
			if (i == 100)
				return (-1);
			
			poll_server_client_socketfd[i].fd = ::connect(client_socket_fd, (sockaddr *)&serv_config, (socklen_t)(sizeof(serv_config)));
			return (0);
		}

		int answer()
		{
			char *sent_answer;
			send(client_socket_fd, sent_answer, strlen(sent_answer), 0);
			return (0);
		}

		std::string crate_dir_tree(char* path_dir)
		{
			std::string dir_tree;
			std::string buf;
			DIR* path = opendir(path_dir);
			struct dirent* dirent_file;
			struct stat* stat_file = NULL;
			dir_tree = "HTTP/1.1 200 OK\r\n\r\n";
			while ((dirent_file = readdir(path)) != NULL)
			{
				if (stat(dirent_file->d_name, stat_file) != -1)
				{
					if (S_ISREG(stat_file->st_mode))
					{
						buf = "<a href=" + (std::string)dirent_file->d_name + " >" + (std::string)dirent_file->d_name + " </a>\n";
						//file S_ISREG
					}
					if (S_ISDIR(stat_file->st_mode))
					{
						buf = "<a href=" + (std::string)dirent_file->d_name + " >" + (std::string)dirent_file->d_name + " </a>\n";
						//dir S_ISDIR
					}
				}
				dir_tree = dir_tree + buf;
				buf.clear();
			}
			dir_tree = dir_tree + "\r\n\r\n";
			return (dir_tree);
		}
	
		// int epull()
		// {
		// 	kqueuefd = kqueue();
		// 	kevent_struct.
		// 	return (0);
		// }
};

#endif
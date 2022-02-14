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
#include "../response_manager/response_manager.hpp"
#include "../Cookies/cookies.hpp"
#include "../response_manager/response_to_get_request.hpp"
#include "../response_manager/response_to_post_request.hpp"
#include "../response_manager/response_to_delete_request.hpp"
#include "../response_manager/response_error_request.hpp"
#include "../response_manager/response_manager.hpp"
#include "chanki.hpp"

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
		size_t count_serv;
		// kqueue
		// int kqueuefd;
		// struct kevent kevent_struct;
		// poll
		// struct pollfd fds[200];
		// select


		// int client_socket_fd;
		// pollfd poll_server_client_socketfd[10];	//плохо
		std::vector<pollfd> _poll_server_client_socketfd;			//хорошо
		std::vector<int> conf_fd;
		std::vector<config_parser> _conf_serv_vec;
		std::vector<std::string> _recv_reader; //что бы поменять на меньший буфер и сохранять сюда request
		int count_client;						//отвратительно
		// std::pair<int, int> pull_server_client_socketfd[100];
		request_manager request;
		// response_manager response;
		cookies _cookies_serv;
		cgi _cgi_scripts;
		// config_parser _conf_serv;


	public:
		serv()
		{

		}

		serv(std::vector<config_parser> conf_serv, cookies cookies_serv, cgi cgi_scripst)
		{
			try
			{
				count_serv = 1;
				count_client = 0;
				int option = 1;
				int ret = 0;
				int error = 0;
				// int error = 0;
				std::vector<config_parser>::iterator it = conf_serv.begin();
				std::vector<config_parser>::iterator it2 = conf_serv.end();
				pollfd one_socket;
				std::string line;

				_cgi_scripts = cgi_scripst;
				_conf_serv_vec = conf_serv;
				count_serv = conf_serv.size();
			 	std::cout << it->get_port() <<std::endl;
				_cookies_serv = cookies_serv;
				while (it != it2)
				{
					bzero((char *) &serv_config, sizeof(serv_config));
					// serv_config.sin_len = 
					serv_config.sin_family = AF_INET;
					serv_config.sin_port = htons(it->get_port());
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
					one_socket.fd = socket_fd;
					one_socket.events = POLLIN;// | POLLOUT;
					// ret = fcntl(socket_fd, F_SETFL, O_NONBLOCK);
					error = serv_bind(socket_fd, serv_config);
					errno = listen(socket_fd, 30000);
					if (error < 0)
					{
						// throw;
					}
					_poll_server_client_socketfd.push_back(one_socket);
					_recv_reader.push_back(line);
					// _conf_serv_vec.push_back(*it);
					it++;
				}
				
			
				// bzero((char *) &serv_config, sizeof(serv_config));
				// // serv_config.sin_len = 
				// serv_config.sin_family = AF_INET;
				// serv_config.sin_port = htons(it->get_port());
				// // serv_config.sin_port = htons(conf_serv.get_listen_port);
				// serv_config.sin_addr.s_addr = INADDR_ANY;
				// bzero(serv_config.sin_zero, 8);
				// // serv_config.sin_addr.s_addr = inet_addr("127.0.0.1"); на приватный ip адресс
				// socket_fd = socket(AF_INET, SOCK_STREAM, 0);
				// ret = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&option, sizeof(option));
				// ret = fcntl(socket_fd, F_SETFL, O_NONBLOCK);
				// // error =  bind(socket_fd, (sockaddr *)serv_config, (socklen_t)(sizeof(serv_config)));
				// // error = listen_fd(); 
				// // epull();
				// for (int i = 0; i < 10; i++)
				// {
				// 	poll_server_client_socketfd[i].fd = -1;
				// 	poll_server_client_socketfd[i].events = 0;
				// 	poll_server_client_socketfd[i].revents = 0;
				// }
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

		int serv_bind(int socket_fd, sockaddr_in serv_config)
		{
			int error = 0;
			try
			{
				error =  bind(socket_fd, (sockaddr *)&serv_config, (socklen_t)(sizeof(serv_config)));
				if (error != 0)
				{
					// throw;
				}
			}
			catch(std::exception &e)
			{
				// throw;
			}
			return (error);
		}//доп

		int accept_serv(int socket_serv)
		{
			int sock_klient = 0;
			try
			{
				sock_klient = accept(socket_serv, 0, 0);
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
		}//доп
		

		int listen_fd()
		{
			try
			{	
				int error = 0;
				std::vector<pollfd>::iterator it = _poll_server_client_socketfd.begin();
				std::vector<pollfd>::iterator it2 = _poll_server_client_socketfd.end();
				
				while (it != it2)
				{
					error = listen(it->fd, 32);
					// if (error < 0)
					// 	throw;
					it++;
				}
				return (error);
			}
			catch(std::exception &e)
			{
				throw;
			}
		}//ок

		int add_client_in_poll(int socket_serv, config_parser conf)
		{
			int new_client = 0;
			int ret;
			std::string new_socket_recv_reader;
			pollfd new_socket;

			if ((new_client = accept_serv(socket_serv)) == -1)
			{
				// throw;
				return (new_client);
			}
			else
			{
				count_client++;
				new_socket.fd = new_client;
				new_socket.events = POLLIN;// | POLLOUT;
				ret = fcntl(new_client, F_SETFL, O_NONBLOCK);
				_poll_server_client_socketfd.push_back(new_socket);
				_conf_serv_vec.push_back(conf);
				_recv_reader.push_back(new_socket_recv_reader);
				return (1);
			}
			return (0);
		}//ок

		int new_client()
		{
			// int new_client = -1;
			size_t i;
			int rc2;
			char buffer[1024];
			int error;
			std::string a;
			bzero(buffer, 1024);
			std::vector<pollfd>::iterator it;
			std::vector<config_parser>::iterator it2;

			try
			{
				while (true)
				{
					rc2 = poll(_poll_server_client_socketfd.data(), _poll_server_client_socketfd.size(), -1);
					i = 0;
					// if (errno != 0)
					// 	std::cout << std::strerror(errno) << errno <<  std::endl;
					while (rc2 > 0 && i < _poll_server_client_socketfd.size())
					{
						if (_poll_server_client_socketfd[i].revents == 0)
						{
							i++;
							continue;
						}
						if (i < count_serv)
						{
							// error = add_client_in_poll(_poll_server_client_socketfd[i].fd);
							error = add_client_in_poll(_poll_server_client_socketfd[i].fd, _conf_serv_vec[i]);
							if (error == 1)
								rc2--;
						}
						else
						{
							if ((_poll_server_client_socketfd[i].revents & POLLIN) == POLLIN)
							{
								check_condition_socket(i, buffer);
								i++;
								continue;
								// rc = recv(_poll_server_client_socketfd[i].fd, buffer, 1024, 0);
								// if (rc == 0)
								// {
								// 	close(_poll_server_client_socketfd[i].fd);
								// 	_recv_reader[i].erase();
								// 	_poll_server_client_socketfd[i].fd = -1;
								// 	rc2--;
								// }
								// if (rc < 0)
								// {
								// 	// std::cout << "error" << std::endl;
								// 	close(_poll_server_client_socketfd[i].fd);
								// 	_recv_reader[i].erase();
								// 	_poll_server_client_socketfd[i].fd = -1;
								// }
								// if (rc > 0)
								// {
								
								
								// usleep(2000);
								// _recv_reader[i] = _recv_reader[i] + buffer;
								// if (_recv_reader[i].find("\r\n\r\n") != std::string::npos)
								// {
								// 	if ((n = _recv_reader[i].find("Content-Type: multipart/form-data; boundary=")) != std::string::npos)//multi if (_requests[socket].find(bound) == std::string::npos)
								// 	{
								// 		std::string boundary;

								// 		boundary = _recv_reader[i].substr(n);
								// 		n = boundary.find("\r\n") - 45;
								// 		boundary = "---" + boundary.substr(45, n) + "--";
								// 		if (_recv_reader[i].find(boundary) != std::string::npos)
								// 			std::cout << "read_more" << std::endl;
								// 	}
								// 	if (_recv_reader[i].find("Content-Length") != std::string::npos)
								// 	{
								// 		if (_recv_reader[i].find("Transfer-Encoding: chunked") != std::string::npos)
								// 		{
								// 			if (_recv_reader[i].find("0/r/n/r/n") != std::string::npos)
								// 				std::cout << "read_more" << std::endl;
								// 			else
								// 			{
								// 				//работа с чанками
								// 			}	
								// 		}
								// 	}
              						
									// std::cout << _recv_reader[i] << std::endl;
									// request = request_manager(_recv_reader[i]);
									// response = response_manager(request, _conf_serv_vec[i]);
									// std::string body_html = response.body_html();
									// rc = send(_poll_server_client_socketfd[i].fd, body_html.c_str(), body_html.length(), 0);
									// close(_poll_server_client_socketfd[i].fd);
									// _recv_reader[i].erase();
									// _poll_server_client_socketfd[i].fd = -1;
								}
								if ((_poll_server_client_socketfd[i].revents & POLLOUT) == POLLOUT)
								{
									write_send(i);
									// _poll_server_client_socketfd[i].events = POLLIN; //?
									close(_poll_server_client_socketfd[i].fd);
									_recv_reader[i].erase();
									_poll_server_client_socketfd[i].fd = -1;
								}
								bzero(buffer, 1024);
							}
							i++;
						}					
				}
			}
			catch(std::exception &e)
			{
				// throw;
			}
			return (0);
		}//доп		
	
		int check_chank_and_multipart(int i)
		{
			(void)i;
			int result = 0;

			return (result);
		}//????????????????????????????

		int check_condition_socket(int i, char *buffer)
		{
			(void)i;
			(void)buffer;
			int result = 0;
			int rc = 0;
			int rc2 = 0;

			if ((_poll_server_client_socketfd[i].revents & POLLIN) == POLLIN)
			{
				rc = recv(_poll_server_client_socketfd[i].fd, buffer, 1024 - 1, 0);
				// if (errno != 0)
				// 	std::cout << std::strerror(errno) << errno <<  std::endl;
				// usleep(1000);
				if (rc == 0)
				{
					close(_poll_server_client_socketfd[i].fd);
					_recv_reader[i].erase();
					_poll_server_client_socketfd[i].fd = -1;
					rc2--;
				}
				if (rc < 0)
				{
					// std::cout << "error" << std::endl;
					close(_poll_server_client_socketfd[i].fd);
					_recv_reader[i].erase();
					_poll_server_client_socketfd[i].fd = -1;
				}
				if (rc > 0)
				{
				// std::cout << POLLIN << std::endl;
					result = reader_recv(i, buffer);
					std::cout << buffer << std::endl;
					if (result == 0)
					{
						// request = request_manager(_recv_reader[i]);
						// response = response_manager(request, _conf_serv_vec[i], _cookies_serv, _cgi_scripts);
						_poll_server_client_socketfd[i].events = POLLOUT;
					}
					else
					{
						return (0);
					}
				}
			}
			// if ((_poll_server_client_socketfd[i].revents & POLLOUT) == POLLOUT)
			// {
			// 	std::cout << POLLOUT << std::endl;
			// 	result = write_send(i);
			// }
			return (result);
		}//переписать

		int reader_recv(int i, char *buffer)
		{
			int result = 0;
			size_t n;
			size_t k ;


			_recv_reader[i] = _recv_reader[i] + buffer;
			if ((k = _recv_reader[i].find("\r\n\r\n")) != std::string::npos)
			{
				if ((n = _recv_reader[i].find("Content-Type: multipart/form-data; boundary=")) != std::string::npos)//multi if (_requests[socket].find(bound) == std::string::npos)
				{
					std::string boundary;
					std::string buf;

					boundary = _recv_reader[i].substr(n);
					n = boundary.find("\r\n") - 45;
					boundary = "---" + boundary.substr(45, n) + "--";
					if (_recv_reader[i].find(boundary) == std::string::npos)
						return (1);
				}
				if (_recv_reader[i].find("Content-Length") != std::string::npos)
				{
					if (_recv_reader[i].find("Transfer-Encoding: chunked") != std::string::npos)
					{
						if (_recv_reader[i].find("0/r/n/r/n") != std::string::npos)
							return (1);
						else
						{
							chanki a(_recv_reader[i]);
							std::string new_recv_reader = a.get_request();
							_recv_reader[i].clear();
							_recv_reader[i] = new_recv_reader;
						}	
					}
				}
			}
			size_t content_length = std::atoi(_recv_reader[i].substr(_recv_reader[i].find("Content-Length: ") + 16, 10).c_str());
			if (_recv_reader[i].size() >= content_length + k + 4 - 1)
				return (0);
			else
				return (1);
			return (result);
		}//ок

		int write_send(int i)
		{
			(void)i;
			int result = 0;
			size_t rc;
			std::string body_html_send;

			request = request_manager(_recv_reader[i]);
			// response = response_manager(request, _conf_serv_vec[i], _cookies_serv, _cgi_scripts);
			body_html_send = body_html(i);
			rc = send(_poll_server_client_socketfd[i].fd, body_html_send.c_str(), body_html_send.length(), 0);
			// close(_poll_server_client_socketfd[i].fd); //?
			_recv_reader[i].erase();
			// _poll_server_client_socketfd[i].fd = -1;  //?
			return (result);
		}

		std::string body_html(int i)
		{
			std::string html;
			std::string html_header;
			std::string html_basement;
			std::string content_file;
			std::string path;
			std::map<std::string, std::map<std::string, std::string> >::iterator _loc;
			std::map<std::string, std::map<std::string, std::string> > _locations;

			if (request.get_name_request() == "GET")
			{
			 	response_to_get_request get(request, _conf_serv_vec[i], _cookies_serv, _cgi_scripts);
				html = get.metod_response();
			}
			if (request.get_name_request() == "POST")
			{
				response_to_post_request post(request, _conf_serv_vec[i], _cookies_serv, _cgi_scripts);
				html = post.metod_response();
			}
			if (request.get_name_request() == "DELETE")
			{
				response_to_delete_request delete_respinse(request, _conf_serv_vec[i], _cookies_serv, _cgi_scripts);
				html = delete_respinse.metod_response();
			}
			if (html.empty())
			{
			// 	html = create_error_page(501);
			}
			return (html);
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
};
// syscall("php filein > file_out")
#endif
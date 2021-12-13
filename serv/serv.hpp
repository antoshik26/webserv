#ifndef SERV_HPP
#define SERV_HPP
#include <iostream>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socet.h>
#include <netdb.h>

#define		serv_port 5000; //считывать с config		 
#define		fd_count 500;

struct in_addr
{
	in_addr_t s_addr;
};

struct sockaddr_in
{
	uint8_t sa_len;
	sa_famaly_t sa_family;
	in_port_t sin_port;
	struct in_addr sin_addr;
	char sin_zero[8];
}; //ipv4

// struct sockaddr_in = {
// 	.sin_famaly = AF_INET;
// 	.sin_addr.s_addr = INADDR_ANY;
// 	.sin_port = htons(serv_port);
// }

class serv
{
	private:
		char* env[];
		struct sockaddr_in serv_config;
		SOCKET socet_serv;


	public:
		serv()
		{

		}

		serv(serv &obj)
		{
			(void)obj;
		}

		serv operator=(serv &obj)
		{
			(void)obj;
		}
		
		~serv()
		{

		}
		

};

#endif
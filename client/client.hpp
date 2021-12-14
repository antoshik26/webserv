#ifndef CLIENT_HPP
#define CLIENT_HPP

class client
{
	private:
		int _fd_sockfd;
	public:
		client()
		{
			_fd_sockfd = 0;
		}

		client(int fd_sockfd)
		{
			_fd_sockfd = fd_sockfd;
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

		}
			
		// void send_info_in_socet()
		// {
		// 	// send
		// }

		int connect_client(int sockfd, sockaddr_in *obj)
		{
			int error = 0;
			try
			{
				error = accept(sockfd, (sockaddr *)obj, (socklen_t*)(sizeof(obj)));
				if (error != 0)
				{
					// throw;
				}
				else
					_fd_sockfd = sockfd; 
			}
			catch(std::exception &e)
			{
				// throw;
			}
			return (error);
		}

		void get_sock(int fd_sockfd)
		{
			_fd_sockfd = fd_sockfd;
		}

		int put_request() //post get delete запросы
		{
			return (1);
		}
};

#endif
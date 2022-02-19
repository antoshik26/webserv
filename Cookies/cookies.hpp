#ifndef COOKIES_HPP
#define COOKIES_HPP
#include <map>
#include <string>
#include <vector>
#include "../config_parser/config_parser.hpp"

class cookies
{
	private:
		std::map<size_t, std::map<std::string, std::string> > _cookies_serv;
	public:
		cookies()
		{

		}

		cookies(std::vector<config_parser> conf_serv)
		{
			int port;
			std::pair<size_t, std::map<std::string, std::string> > cookies_pair;
			std::map<size_t, std::map<std::string, std::string> >::iterator it;
			std::map<std::string, std::string> value_cookies;
			std::pair<std::string, std::string> obj;
			std::vector<config_parser>::iterator it2 = conf_serv.begin();
			std::vector<config_parser>::iterator it3 = conf_serv.end();

			while (it2 != it3)
			{
				port = it2->get_port();
				if (port == 7000)
				{
					obj.first = "Username";
					obj.second = "XYZ";
					value_cookies.insert(obj);
					obj.first = "Password";
					obj.second = "XYZ123";
					value_cookies.insert(obj);
					cookies_pair.first = port;
					cookies_pair.second = value_cookies;
					_cookies_serv.insert(cookies_pair);
				}
				if (port == 8000)
				{

				}
				if (port == 9000)
				{

				}
				it2++;
			}
		}

		~cookies()
		{

		}

		std::map<std::string, std::string> get_cookies(size_t port)
		{
			std::map<std::string, std::string> cookies_serv;
			std::map<size_t, std::map<std::string, std::string> >::iterator it;
			if ((it = _cookies_serv.find(port)) != _cookies_serv.end())
			{
				cookies_serv = it->second;
			}
			return (cookies_serv);
		}

		// void set_cookies(std::map<std::string, std::string> new_cookies)
		// {

		// }
	private:
		

};

#endif
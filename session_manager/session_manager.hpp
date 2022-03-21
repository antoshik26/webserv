#ifndef SESSION_MANAGER_HPP
#define SESSION_MANAGER_HPP
#include "../config_parser/config_parser.hpp"
#include <string>
#include <map>

class session_manager
{
	private:
		std::map<std::string, std::string> sesion_identifier;
		std::map<size_t, std::map<std::string, std::string> > session_identifier;
	public:
		session_manager()
		{
		}
	
		session_manager(std::vector<config_parser> conf_serv)
		{
			std::vector<config_parser>::iterator it = conf_serv.begin();
			std::vector<config_parser>::iterator it2 = conf_serv.end();
			std::pair<size_t, std::map<std::string, std::string> >pair_session_identifier;
			while (it != it2)
			{
				pair_session_identifier.first = it->get_port();
				session_identifier.insert(pair_session_identifier);
				it++;
			}
		}

		~session_manager()
		{}

		std::string creating_identifier_session(int port)
		{
			std::string sesion_identifier_client;
			std::string collor_backgraund;
			std::pair<std::string, std::string> pair_identifier;
			std::map<size_t, std::map<std::string, std::string> >::iterator it;

			sesion_identifier_client = rand_identifier();
			if (sesion_identifier.find(sesion_identifier_client) == sesion_identifier.end())
			{
				sesion_identifier_client = rand_identifier();
				pair_identifier.first = sesion_identifier_client;
				collor_backgraund = rand_collor_backgraund();
				pair_identifier.second = collor_backgraund;
				it = session_identifier.find(port);
				it->second.insert(pair_identifier);
				// pair_session.first = port;
				// pair_session.second.insert(pair_identifier);
				// session_identifier.insert(pair_session);
				// session_identifier.insert(pair_identifier);
			}
			return (pair_identifier.first);
		}

		void creating_identifier_session(std::string identifier, int port)
		{
			std::string collor_backgraund;
			std::pair<std::string, std::string> pair_identifier;
			std::map<size_t, std::map<std::string, std::string> >::iterator it;

			if (sesion_identifier.find(identifier) == sesion_identifier.end())
			{
				pair_identifier.first = identifier;
				collor_backgraund = rand_collor_backgraund();
				pair_identifier.second = collor_backgraund;
				it = session_identifier.find(port);
				it->second.insert(pair_identifier);
				// pair_session.first = port;
				// pair_session.second.insert(pair_identifier);
				// session_identifier.insert(pair_session);
				// sesion_identifier.insert(pair_identifier);
			}
			return;
		}

		std::pair<std::string, std::string> find_client_session(std::string identifier, int port)
		{
			std::map<std::string, std::string>::iterator it;
			std::pair<std::string, std::string> it_pair;
			std::map<size_t, std::map<std::string, std::string> >::iterator it2;

			if (session_identifier.find(port) != session_identifier.end())
			{
				it2 = session_identifier.find(port);
				if (it2->second.find(identifier) != it2->second.end())
				{
					it = it2->second.find(identifier);
					it_pair.first = it->first;
					it_pair.second = it->second;
				}
			}
			return (it_pair);
		}

	private:
		std::string rand_identifier()
		{
			std::string identifier;
			size_t i = 0;

			while (i < 10)
			{
				identifier.push_back(getRandomSymbol());
				i++;
			}
			return (identifier);
		}
		
		char getRandomSymbol()
		{
			char ch;
			unsigned short tmp;
			tmp = rand() % ('Z' - 'A' + 1) + 'A';
			ch = tmp;
			return ch;
		}
		
		std::string rand_collor_backgraund()
		{
			std::string collor_backgraund;
			size_t i = 0;
			char b;
			int ch;

			while (i < 6)
			{
				ch = getRandomInt();
				if (ch >= 10)
					b = 65 + ch - 10;
				else
					b = 48 + ch;
				collor_backgraund.push_back(b);
				i++;
			}
			// std::cout << collor_backgraund << std::endl;
			return (collor_backgraund);
		}

		int getRandomInt()
		{
			int a;
			
			a = rand() % 16;
			return (a);
		}
};
#endif
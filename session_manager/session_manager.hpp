#ifndef SESSION_MANAGER_HPP
#define SESSION_MANAGER_HPP
#include "../config_parser/config_parser.hpp"
#include <string>
#include <map>

class session_manager
{
	private:
		std::map<std::string, std::string> sesion_identifier;
		// std::map<size_t, std::map<std::string, std::string> sesion_identifier;
	public:
		session_manager()
		{}

		~session_manager()
		{}

		std::string creating_identifier_session()
		{
			std::string sesion_identifier_client;
			std::string collor_backgraund;
			std::pair<std::string, std::string> pair_identifier;

			sesion_identifier_client = rand_identifier();
			if (sesion_identifier.find(sesion_identifier_client) == sesion_identifier.end())
			{
				sesion_identifier_client = rand_identifier();
				pair_identifier.first = sesion_identifier_client;
				collor_backgraund = rand_collor_backgraund();
				pair_identifier.second = collor_backgraund;
				sesion_identifier.insert(pair_identifier);
			}
			return (pair_identifier.first);
		}

		void creating_identifier_session(std::string identifier)
		{
			std::string sesion_identifier_client;
			std::string collor_backgraund;
			std::pair<std::string, std::string> pair_identifier;

			sesion_identifier_client = rand_identifier();
			if (sesion_identifier.find(sesion_identifier_client) == sesion_identifier.end())
			{
				sesion_identifier_client = rand_identifier();
				pair_identifier.first = sesion_identifier_client;
				collor_backgraund = rand_collor_backgraund();
				pair_identifier.second = collor_backgraund;
				sesion_identifier.insert(pair_identifier);
			}
			return;
		}

		std::pair<std::string, std::string> find_client_session(std::string identifier)
		{
			std::map<std::string, std::string>::iterator it;
			std::pair<std::string, std::string> it_pair;

			// it->first.clear();
			// it->second.clear();
			if (sesion_identifier.find(identifier) != sesion_identifier.end())
			{
				it = sesion_identifier.find(identifier);
				it_pair.first = it->first;
				it_pair.second = it->second;
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
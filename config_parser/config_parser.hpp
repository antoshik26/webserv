#ifndef CONFIG_PARSER_HPP
#define CONFIG_PARSER_HPP
#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>

class config_parser
{
	private:
		int _port;
		bool _avtoindex;
		std::string serv_name;
		std::map<std::string, std::vector<std::string> > _dir_extensions;
		std::map<std::string, std::vector<std::string> > _locations;
		std::map<std::string, std::vector<std::string> > _cgi;
	public:
		config_parser(std::string config_serv)
		{
			(void)config_serv;
			find_port(config_serv);
			find_avtoindex(config_serv);
		}

		~config_parser()
		{
		}
		
		std::map<std::string, std::vector<std::string> > get_dir_extensions()
		{
			return (_dir_extensions);
		}

		std::map<std::string, std::vector<std::string> > get_locations()
		{
			return (_locations);
		}
		
		std::map<std::string, std::vector<std::string> > get_cgi()
		{
			return (_cgi);
		}

		bool get_avtoindex()
		{
			return (_avtoindex);
		}

		int get_port()
		{
			return(_port);
		}

	private:
		void find_port(std::string config_serv)
		{
			size_t n;
			size_t i;
			std::string line;

			if ((n = config_serv.find("listen")) != std::string::npos)
			{
				while (config_serv[n] != ':')
					n++;
				n++;
				while (config_serv[n] == ' ')
					n++;
				i = n;
				while (config_serv[n] !=  '\n')
					n++;
				line = config_serv.substr(i, n);
				// _port = atoi((char*)line);
			}
		}

		void find_avtoindex(std::string config_serv)
		{
			size_t n;
			size_t i;
			std::string line;

			if ((n = config_serv.find("avtoindex") != std::string::npos)
			{
				while (config_serv[n] != ':')
					n++;
				n++;
				while (config_serv[n] == ' ')
					n++;
				i = n;
				while (config_serv[n] !=  '\n')
					n++;
				line = config_serv.substr(i, n);
				if (line == "on")
					_avtoindex = true;
				else	
					_avtoindex = false;
			}
		}

		void find_dir_extensions(std::string config_serv)
		{
			(void)config_serv;
		}
		
		void find_locations(std::string config_serv)
		{
			(void)config_serv;
		}

		void find_cgi(std::string config_serv)
		{
			(void)config_serv;
		}
};

#endif
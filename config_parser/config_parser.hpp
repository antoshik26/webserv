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
		std::string _serv_name;
		std::string _access_log;
		std::string _error_log;
		std::map<std::string, std::vector<std::string> > _locations; //?
		// std::map<std::string, std::map<std::string, std::string> > _locations;
		std::map<std::string, std::map<std::string, std::string> > _cgi; //подумать над таким выводом
	public:
		config_parser()
		{

		}

		config_parser(std::string config_serv)
		{
			(void)config_serv;
			find_port(config_serv);
			find_server_name(config_serv);
			find_avtoindex(config_serv);
			find_locations(config_serv);
		}

		~config_parser()
		{
		}
		
		std::map<std::string, std::vector<std::string> > get_locations()
		{
			return (_locations);
		}
		
		std::map<std::string, std::map<std::string, std::string> > get_cgi()
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
				while (config_serv[n] != ' ')
					n++;
				n++;
				while (config_serv[n] == ' ')
					n++;
				i = n;
				while (config_serv[n] !=  ';')
					n++;
				line = config_serv.substr(i, n);
				_port = atoi(line.c_str());
			}
		}

		void find_avtoindex(std::string config_serv)
		{
			size_t n;
			size_t i;
			std::string line;

			if ((n = config_serv.find("avtoindex")) != std::string::npos)
			{
				while (config_serv[n] != ' ')
					n++;
				n++;
				while (config_serv[n] == ' ')
					n++;
				i = n;
				while (config_serv[n] !=  ';')
					n++;
				line = config_serv.substr(i, n);
				if (line == "on")
					_avtoindex = true;
				else	
					_avtoindex = false;
			}
		}
		
		void find_locations(std::string config_serv)
		{
			(void)config_serv;
			size_t n;
			size_t i;
			std::string line;
			std::string extensions;
			std::pair<std::string, std::map<std::string, std::string> > pair_cgi_param;

			
			while ((n = config_serv.find("location")) != std::string::npos)
			{
				i = n;
				while (config_serv[i] != '/' || config_serv[i] != '~')
					i++;
				if (config_serv[i] == '/')
				{
					find_root(config_serv);
					find_index(config_serv);
				}
				else
				{
					while(config_serv[i] != '.')
						i++;
					n = i;
					while(config_serv[i] != '$')
						i++;
					extensions = config_serv.substr(n, i);
					find_cgi_include(config_serv, extensions);
					find_pass(config_serv, extensions);
					find_cgi_index(config_serv, extensions);
					find_cgi_param(config_serv, extensions);
				}
			}
		}

		void find_cgi_include(std::string config_serv, std::string exception)
		{
			(void)config_serv;
			(void)exception;
			size_t n;
			size_t i;
			std::pair<std::string, std::map<std::string, std::string> > obj;
			std::pair<std::string, std::string> map_obj;
			std::string index;
			std::string line;

			if ((n = config_serv.find("include")) != std::string::npos)
			{
				while (config_serv[n] != ' ')
					n++;
				while (config_serv[n] == ' ')
					n++;
				i = n;
				while (config_serv[n] !=  ';')
					n++;
				line = config_serv.substr(i, n);
				obj.first = exception;
				map_obj.first = "include";
				map_obj.second = line;
				obj.second.insert(map_obj);
				_cgi.insert(obj);
			}
		}

		void find_cgi_pass(std::string config_serv, std::string exception)
		{
			(void)config_serv;
			(void)exception;
			size_t n;
			size_t i;
			std::pair<std::string, std::map<std::string, std::string> > obj;
			std::pair<std::string, std::string> map_obj;
			std::string index;
			std::string line;

			if ((n = config_serv.find("cgi_puss")) != std::string::npos)
			{
				while (config_serv[n] != ' ')
					n++;
				while (config_serv[n] == ' ')
					n++;
				i = n;
				while (config_serv[n] !=  ';')
					n++;
				line = config_serv.substr(i, n);
				obj.first = exception;
				map_obj.first = "cgi_puss";
				map_obj.second = line;
				obj.second.insert(map_obj);
				_cgi.insert(obj);
			}
		}

		void find_cgi_index(std::string config_serv, std::string exception)
		{
			(void)config_serv;
			(void)exception;
			size_t n;
			size_t i;
			std::pair<std::string, std::map<std::string, std::string> > obj;
			std::pair<std::string, std::string> map_obj;
			std::string index;
			std::string line;

			if ((n = config_serv.find("cgi_index")) != std::string::npos)
			{
				while (config_serv[n] != ' ')
					n++;
				while (config_serv[n] == ' ')
					n++;
				i = n;
				while (config_serv[n] !=  ';')
					n++;
				line = config_serv.substr(i, n);
				obj.first = exception;
				map_obj.first = "cgi_index";
				map_obj.second = line;
				obj.second.insert(map_obj);
				_cgi.insert(obj);
			}
		}

		void find_cgi_param(std::string config_serv, std::string exception)
		{
			(void)config_serv;
			(void)exception;
			size_t n;
			size_t i;
			std::pair<std::string, std::map<std::string, std::string> > obj;
			std::pair<std::string, std::string> map_obj;
			std::string index;
			std::string line;

			if ((n = config_serv.find("cgi_param")) != std::string::npos)
			{
				while (config_serv[n] != ' ')
					n++;
				while (config_serv[n] == ' ')
					n++;
				i = n;
				while (config_serv[n] !=  ';')
					n++;
				line = config_serv.substr(i, n);
				obj.first = exception;
				map_obj.first = "cgi_param";
				map_obj.second = line;
				obj.second.insert(map_obj);
				_cgi.insert(obj);
			}
		}

		void find_access_log(std::string config_serv)
		{
			(void)config_serv;
			size_t n;
			size_t i;

			if ((n = config_serv.find("access_log")) != std::string::npos)
			{
				while (config_serv[n] != ' ')
					n++;
				n++;
				while (config_serv[n] == ' ')
					n++;
				i = n;
				while (config_serv[n] !=  ';')
					n++;
				_access_log = config_serv.substr(i, n);
			}
		}

		void find_error_log(std::string config_serv)
		{
			(void)config_serv;
			size_t n;
			size_t i;

			if ((n = config_serv.find("error_log")) != std::string::npos)
			{
				while (config_serv[n] != ' ')
					n++;
				n++;
				while (config_serv[n] == ' ')
					n++;
				i = n;
				while (config_serv[n] !=  ';')
					n++;
				_error_log = config_serv.substr(i, n);
			}
		}
		
		void find_server_name(std::string config_serv)
		{
			size_t n;
			size_t i;

			if ((n = config_serv.find("server_name")) != std::string::npos)
			{
				while (config_serv[n] != ' ')
					n++;
				n++;
				while (config_serv[n] == ' ')
					n++;
				i = n;
				while (config_serv[n] !=  ';')
					n++;
				_serv_name = config_serv.substr(i, n);
			}
		}

		void find_pass(std::string config_serv, std::string exception)
		{
			(void)config_serv;
			size_t n;
			size_t i;
			std::pair<std::string, std::map<std::string, std::string> > obj;
			std::pair<std::string, std::string> map_obj;
			std::string index;
			std::string line;

			if ((n = config_serv.find("pass")) != std::string::npos)
			{
				while (config_serv[n] != ' ')
					n++;
				while (config_serv[n] == ' ')
					n++;
				i = n;
				while (config_serv[n] !=  ';')
					n++;
				line = config_serv.substr(i, n);
				obj.first = exception;
				map_obj.first = "pass";
				map_obj.second = line;
				obj.second.insert(map_obj);
				_cgi.insert(obj);
			}
		}

		void find_root(std::string config_serv)
		{
			size_t n;
			size_t i;
			std::pair<std::string, std::vector<std::string> > obj;
			std::string root;

			if ((n = config_serv.find("server_name")) != std::string::npos)
			{
				while (config_serv[n] != ' ')
					n++;
				while (config_serv[n] == ' ')
					n++;
				i = n;
				while (config_serv[n] !=  ';')
					n++;
				root = config_serv.substr(i, n);
				obj.first = "root";
				obj.second.push_back(root);
				_locations.insert(obj);
			}
		}

		void find_index(std::string config_serv)
		{
			size_t n;
			size_t i;
			std::pair<std::string, std::vector<std::string> > obj;
			std::string index;
			std::string line;

			if ((n = config_serv.find("index")) != std::string::npos)
			{
				while (config_serv[n] != ' ')
					n++;
				n++;
				while (config_serv[n] == ' ')
					n++;
				i = n;
				while (config_serv[n] !=  ';')
					n++;
				index = config_serv.substr(i, n);
				obj.first = "index";
				i = 0;
				n = 0;
				while (index[i])
				{
					if (index[i] == ' ' || index[i])
					{
						line = index.substr(n, i);
						obj.second.push_back(line);
						n = i;
					}
					i++;
				}
				_locations.insert(obj);
			}
		}
};

#endif
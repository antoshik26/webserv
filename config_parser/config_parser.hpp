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
		std::string _return;
		std::map<std::string, std::map<std::string, std::string> > _locations;
		std::map<std::string, std::map<std::string, std::string> > _cgi;
	public:
		config_parser()
		{

		}

		config_parser(std::string config_serv)
		{
			(void)config_serv;
			find_port(config_serv);
			find_return(config_serv);
			find_server_name(config_serv);
			find_avtoindex(config_serv);
			find_locations(config_serv);
		}

		~config_parser()
		{
		}
		
		std::map<std::string, std::map<std::string, std::string> > get_locations()
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

		std::string get_return()
		{
			return(_return);
		}

	private:
		void find_return(std::string config_serv)
		{
			size_t n;
			size_t i;
			std::string line;

			if ((n = config_serv.find("return")) != std::string::npos)
			{
				n = config_serv.find("307"); //парсинг номера в мапу
				while (config_serv[n] != ' ')
					n++;
				n++;
				while (config_serv[n] == ' ')
					n++;
				i = n;
				while (config_serv[n] != ';')
					n++;
				line = config_serv.substr(i, n - i);
				_return = line;
			}

		}
	
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

			if ((n = config_serv.find("autoindex")) != std::string::npos)
			{
				while (config_serv[n] != ' ')
					n++;
				n++;
				while (config_serv[n] == ' ')
					n++;
				i = n;
				while (config_serv[n] !=  ';')
					n++;
				line = config_serv.substr(i, n - i);
				// std::cout << line << std::endl;
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
			size_t a;
			size_t i;
			std::string line;
			std::string extensions;
			std::pair<std::string, std::map<std::string, std::string> > pair_cgi_param;

			// std::cout<< config_serv <<std::endl;
			n = 0;
			while ((n = config_serv.find("location", n)) != std::string::npos)
			{
				i = n;
				n = n + 8;
				while (config_serv[i] != '/' && config_serv[i] != '~')
				{
					// std::cout << config_serv[i] << std::endl;
					i++;
				}
				if (config_serv[i] == '/')
				{
					extensions = "/"; 
					find_root(config_serv, extensions);
					find_index(config_serv, extensions);
				}
				else
				{
					a = config_serv.find("location", n);
					line = config_serv.substr(n, a - n);
					i = 0;
					// std::cout << line << std::endl;
					while (line[i] != '.')
						i++;
					a = i;
					while(line[i] != '$')
						i++;
					extensions = line.substr(a, i - a);
					if (extensions == ".php" || extensions == ".py")
					{
						find_cgi_include(line, extensions);
						find_cgi_pass(line, extensions);
						find_cgi_index(line, extensions);
						find_cgi_param(line, extensions);
					}
					else
						find_pass(line, extensions);
					// while(config_serv[i] != '.')
					// 	i++;
					// n = i;
					// while(config_serv[i] != '$')
					// 	i++;
					// extensions = config_serv.substr(n, i - n);
					// if (extensions == ".cs" || extensions == ".py")
					// {
					// 	find_cgi_include(config_serv, extensions);
					// 	find_cgi_pass(config_serv, extensions);
					// 	find_cgi_index(config_serv, extensions);
					// 	find_cgi_param(config_serv, extensions);
					// }
					// else
					// 	find_pass(config_serv, extensions);
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
				line = config_serv.substr(i, n - i);
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
			std::map<std::string, std::map<std::string, std::string> >::iterator obj;
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
				line = config_serv.substr(i, n - i);
				obj = _cgi.find(exception);
				map_obj.first = "cgi_puss";
				map_obj.second = line;
				obj->second.insert(map_obj);
				// _cgi.insert(obj);
			}
		}

		void find_cgi_index(std::string config_serv, std::string exception)
		{
			(void)config_serv;
			(void)exception;
			size_t n;
			size_t i;
			std::map<std::string, std::map<std::string, std::string> >::iterator obj;
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
				line = config_serv.substr(i, n - i);
				obj = _cgi.find(exception);
				map_obj.first = "cgi_index";
				map_obj.second = line;
				obj->second.insert(map_obj);
				// _cgi.insert(obj);
			}
		}

		void find_cgi_param(std::string config_serv, std::string exception)
		{
			(void)config_serv;
			(void)exception;
			size_t n;
			size_t i;
			std::map<std::string, std::map<std::string, std::string> >::iterator obj;
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
				line = config_serv.substr(i, n - i);
				obj = _cgi.find(exception);
				map_obj.first = "cgi_param";
				map_obj.second = line;
				obj->second.insert(map_obj);
				// _cgi.insert(obj);
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
				line = config_serv.substr(i, n - i);
				obj.first = exception;
				// obj = _cgi.find(exception);
				map_obj.first = "pass";
				map_obj.second = line;
				obj.second.insert(map_obj);
				_cgi.insert(obj);
			}
		}

		void find_root(std::string config_serv, std::string exception)
		{
			size_t n;
			size_t i;
			// std::pair<std::string, std::vector<std::string> > obj;
			std::pair<std::string, std::map<std::string, std::string> > obj;
			std::pair<std::string, std::string> obj_map;
			std::string root;

			if ((n = config_serv.find("root")) != std::string::npos)
			{
				while (config_serv[n] != ' ')
					n++;
				while (config_serv[n] == ' ')
					n++;
				i = n;
				while (config_serv[n] !=  ';')
					n++;
				root = config_serv.substr(i, n - i);
				obj.first = exception;
				obj_map.first = "root";
				obj_map.second = root;
				obj.second.insert(obj_map);
				_locations.insert(obj);
			}
		}

		void find_index(std::string config_serv, std::string exception)
		{
			size_t n;
			size_t i;
			std::map<std::string, std::map<std::string, std::string> >::iterator obj;
			std::pair<std::string, std::string> obj_map;
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
				index = config_serv.substr(i, n - i);
				// obj.first = "index";
				i = 0;
				n = 0;
				// while (index[i])
				// {
				// 	if (index[i] == ' ' || !index[i])
				// 	{
				// 		line = index.substr(n, i - n);
				// 		obj.second.push_back(line);
				// 		n = i;
				// 	}
				// 	i++;
				// }
				// line = index.substr(n, i - n);
				obj = _locations.find(exception);
				obj_map.first = "index";
				obj_map.second = index;
				obj->second.insert(obj_map);
				// obj.second.push_back(line);
				// _locations.insert(obj);
			}
		}
};

#endif
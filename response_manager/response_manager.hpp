#ifndef RESPONSE_MANAGER_HPP
#define RESPONSE_MANAGER_HPP
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include "../request_manager/request_manager.hpp"
#include "../config_parser/config_parser.hpp"

class response_manager
{
	private:
		request_manager _request;
		config_parser _conf;
		std::string response;
	public:
		response_manager()
		{

		}

		response_manager(request_manager request, config_parser conf)
		{
			_request = request;
			_conf = conf;
		}
		//оператор копирование 
		//оператор присваивания

		~response_manager()
		{
		}

		std::string crate_dir_tree(const char* path_dir)
		{
			std::string dir_tree;
			std::string buf;
			DIR* path = opendir(path_dir);
			struct dirent* dirent_file;
			struct stat stat_file;
			dir_tree = dir_tree + "<!DOCTYPE html>\n<html>\n<body>\n";
			while ((dirent_file = readdir(path)) != NULL)
			{
				if (stat(dirent_file->d_name, &stat_file) != -1)
				{
					if (S_ISREG(stat_file.st_mode))
					{
						buf = "<a href=\"" + (std::string)dirent_file->d_name + "\">" + (std::string)dirent_file->d_name + "</a>\n";
						std::cout << buf <<std::endl;
					}
					if (S_ISDIR(stat_file.st_mode))
					{
						buf = "<a href=" + (std::string)dirent_file->d_name + " >" + (std::string)dirent_file->d_name + " </a>\n";
						std::cout << buf <<std::endl;
					}
				}
				dir_tree = dir_tree + buf;
				buf.clear();
			}
			dir_tree = dir_tree + "</body> \n</html>\n";
			std::cout << dir_tree << std::endl;
			return (dir_tree);
		}

		int error()
		{

			return (0);
		}

		std::string body_html()
		{
			std::string html;
			std::string html_header;
			std::string html_basement;
			std::string content_file;
			std::string path;
			std::map<std::string, std::map<std::string, std::string> >::iterator _loc;
			std::map<std::string, std::map<std::string, std::string> > _locations;
			struct stat stat_file;
			int error;

			if (_request.get_name_request() == "GET")
				html = metod_get();
			if (_request.get_name_request() == "POST")
				html = metod_post();	
			if (_request.get_name_request() == "DELETE")
				html = metod_delete();
			if (html.empty())
				html = create_error_page(501);
			return (html);
		}

		std::string create_error_page(int error)
		{
			std::string html_error;
			if (error == 500)
				html_error = error_500();
			if (error == 404)
				html_error = error_404();
			if (error ==501)
				html_error = error_501();
			return (html_error);
		}

	private:
		std::string read_full_file(std::string path_to_file)
		{
			std::string file;
			std::string line;
			std::ifstream fs;

			fs.open(path_to_file);
			if (fs.is_open())
			{
				while (getline(fs, line))
				{
					file = file + line + "\n";
					line.clear();
				}
			}
			return (file);
		}

		std::string html_header()
		{
			std::string html_header = "HTTP/1.1 200 OK\r\n\r\n";
			return(html_header);
		}

		std::string html_basement()
		{
			std::string html_basement = "\r\n\r\n";
			return(html_basement);
		}

		std::string error_500()
		{
			std::string body_html;

			body_html = "HTTP/1.1 500 Internal Server Error\r\n\r\n";
			body_html = body_html + "<!DOCTYPE html>";
			body_html = body_html + "<html>";
			body_html = body_html + "<body>";
			body_html = body_html + "<h1>500</h1>";
			body_html = body_html + "</body>";
			body_html = body_html + "</html>";
			// body_html = body_html + html_basement();
			return (body_html);
		}

		std::string error_404()
		{
			std::string body_html;

			body_html = "HTTP/1.1 404 Not Found\r\n\r\n";
			body_html = body_html + "<!DOCTYPE html>";
			body_html = body_html + "<html>";
			body_html = body_html + "<body>";
			body_html = body_html + "<h1>404</h1>";
			body_html = body_html + "</body>";
			body_html = body_html + "</html>";
			// body_html = body_html + html_basement();
			return (body_html);
		}

		std::string error_501()
		{
			std::string body_html;
			
			body_html = "HTTP/1.1 501 Not Implemented\r\n\r\n";
			body_html = body_html + "<!DOCTYPE html>";
			body_html = body_html + "<html>";
			body_html = body_html + "<body>";
			body_html = body_html + "<h1>501</h1>";
			body_html = body_html + "</body>";
			body_html = body_html + "</html>";
			// body_html = body_html + html_basement();
			return (body_html);
		}
		
		std::string return_page()
		{
			std::string body_html;

			body_html = "HTTP/1.1 301 Moved Permanently\n";
			body_html = body_html + "Location: " + _conf.get_return();
			return (body_html);
		}

		std::string find_path_to_html()
		{
			size_t i = 0;
		 	const char* stat_path;
			char buf[1000];
			std::string path;
			std::map<std::string, std::map<std::string, std::string> > _locations;
			std::vector<std::string> split_file;
			std::string path_and_file = "";
			struct stat stat_file;
			std::map<std::string, std::map<std::string, std::string> >::iterator it = _locations.begin();

			_locations = _conf.get_locations();
			for (std::map<std::string, std::map<std::string, std::string> >::iterator it = _locations.begin(); it != _locations.end(); it++)
			{
				if (_request.get_page_index() == it->first)
				{
					split_file = split((it->second).find("index"));
					path = (it->second).find("root")->second;
					while (i < split_file.size())
					{
						path_and_file = path + split_file[i];
						stat_path = path_and_file.c_str();
						if (stat(stat_path, &stat_file) != -1) //&& S_ISDIR(stat_file.st_mode)) //НЕ ПАПКА
						{
							return (path_and_file);
						}
						path_and_file.clear();
						i++;
					}
				}
			}
			if (path_and_file.empty())
			{
				path = _locations.find("/")->second.find("root")->second;
				if (!(_locations.find("/")->second.find("index")->second.empty()))
					path_and_file = path + _request.get_page_index();
			}
			return (path_and_file);
		}

		std::string find_path_to_cgi()
		{
			size_t i = 0;
			size_t n = 0;
		 	const char* stat_path;
			char buf[1000];
			std::string path;
			std::map<std::string, std::map<std::string, std::string> > _cgi;
			std::map<std::string, std::map<std::string, std::string> >::iterator it;
			std::vector<std::string> split_file;
			std::string path_and_file;
			struct stat stat_file;
			std::string line;
			
			line = _request.get_page_index().substr(_request.get_page_index().find(".") + 1, _request.get_page_index().length());
			_cgi = _conf.get_cgi();
			for (std::map<std::string, std::map<std::string, std::string> >::iterator it = _cgi.begin(); it != _cgi.end(); it++)
			{
				if (it->first.find(line) != std::string::npos)
				{
					path = (it->second).find("pass")->second;
					path_and_file = path + _request.get_page_index();
					stat_path = path_and_file.c_str();
					if (stat(stat_path, &stat_file) != -1)
					{
						return (path_and_file);
					}
				}
			}
			return (path_and_file);
		}

		int definition_path_or_filr(std::string file_or_path)
		{
			(void)file_or_path;
			int a = 0;

			if (file_or_path.find(".") != std::string::npos && file_or_path.find("html") == std::string::npos)
				a = 1;
			return a;
		}

		std::vector<std::string> split(std::map<std::string, std::string>::iterator it)
		{
			std::vector<std::string> split_file;
			std::string page_location = it->second;
			std::string line;
			int i = 0;
			int n = 0;

			while (page_location[i])
			{
				if (page_location[i] == ' ')
				{
					line = page_location.substr(n, i - n);
					split_file.push_back(line);
					line.clear();
					n = i + 1;
				}
				i++;
			}
			line = page_location.substr(n, i - n);
			split_file.push_back(line);
			return (split_file);
		}

		std::string metod_get() //переделать стуктуру создание get от ответа полностью
		{
			std::string html;
			std::string html_header;
			std::string html_basement;
			std::string content_file;
			std::string path;
			std::map<std::string, std::map<std::string, std::string> >::iterator _loc;
			std::map<std::string, std::map<std::string, std::string> > _locations;
			struct stat stat_file;

			html_header = this->html_header();
			html = html + html_header;
			html_basement = this->html_basement();
			if (definition_path_or_filr(_request.get_page_index()) == 0)	//path //вынести в работу с путями
			{
				path = find_path_to_html();
				// if (definition_path_or_filr(path) == 0)
				if (path.empty())
				{
					if (_conf.get_avtoindex() == true)
					{
						if (stat(path.c_str(), &stat_file) != -1)
						{
							if (S_ISDIR(stat_file.st_mode))
							{
								html = html + crate_dir_tree((path).c_str());
							}
						}
					}
					else
					{
						if (_conf.get_return().empty())
							html = create_error_page(404);
						else
						{
							html = return_page();
							if (html.empty())
								html = create_error_page(404);
						}
					}
				}
				else
				{
					if (stat(path.c_str(), &stat_file) != -1)
						html = html + read_full_file(path);
					else
						html = create_error_page(404);
				}
			}
			else								//file
			{
				path = find_path_to_cgi();
				if (path.empty())
				{
					// if (stat(path.c_str(), stat_file) != -1)
					// {
					// 	if (S_ISREG(stat_file->st_mode))
					// 	{
					// 		html = html + read_full_file(path);
					// 	}
					// 	else
					// 	{
					// 		// rewrite ^ https://$host$request_uri? <флаг>;
					// 		create_error_page(404); 
					// 	}
					// }
					// else
					// {
					// 	// rewrite ^ https://$host$request_uri? <флаг>;
					// 	create_error_page(404); 
					// }
				}
				else
				{
					if (stat(path.c_str(), &stat_file) != -1)
						html = html + read_full_file(path);
					else
						html = create_error_page(404);
				}
			}
			html = html + html_basement;
			return (html);
		}

		std::string metod_post()
		{
			std::string html;
			std::string html_header;
			std::string html_basement;
			std::string content_file;
			std::string path;
			std::map<std::string, std::map<std::string, std::string> >::iterator _loc;
			std::map<std::string, std::map<std::string, std::string> > _locations;
			struct stat stat_file;

			// if(_request)
			// {

			// }
			return (html);
		}

		std::string metod_delete()
		{
			std::string html;
			
			return (html);
		}
};

#endif
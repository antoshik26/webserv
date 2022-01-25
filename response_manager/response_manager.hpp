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
			dir_tree = "HTTP/1.1 200 OK\r\n\r\n";
			while ((dirent_file = readdir(path)) != NULL)
			{
				if (stat(dirent_file->d_name, &stat_file) != -1)
				{
					if (S_ISREG(stat_file.st_mode))
					{
						buf = "<a href=" + (std::string)dirent_file->d_name + " >" + (std::string)dirent_file->d_name + " </a>\n";
						//file S_ISREG
					}
					if (S_ISDIR(stat_file.st_mode))
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

			if ((error = this->error()) == 0)
			{
				html_header = this->html_header();
				html = html + html_header;
				html_basement = this->html_basement();
				if (definition_path_or_filr(_request.get_page_index()) == 0)	//path //вынести в работу с путями
				{
					path = find_path_to_html();
					if (path.empty())
					{
						if (_conf.get_avtoindex() == true)
						{
							if (stat(path.c_str(), &stat_file) != -1)
							{
								if (S_ISDIR(stat_file.st_mode))
								{
									crate_dir_tree((_request.get_page_index()).c_str());
								}
							}
						}
						else
						{
							// rewrite ^ https://$host$request_uri? <флаг>;
							create_error_page(404); 
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
				else								//file /вынести в функцию работы с файлами /чанки /сокеты
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
			}
			else
			{
				// rewrite ^ https://$host$request_uri? <флаг>;
				create_error_page(500); 
			}
			html = html + html_basement;
			return (html);
		}


		// std::string body_html()
		// {
		// 	std::string html;
		// 	std::string html_header;
		// 	std::string html_basement;
		// 	std::string content_file;
		// 	std::string path;
		// 	std::map<std::string, std::map<std::string, std::string> >::iterator _loc;
		// 	std::map<std::string, std::map<std::string, std::string> > _locations;
		// 	struct stat* stat_file = NULL;
		// 	int error;

		// 	if ((error = this->error()) == 0)
		// 	{
		// 		html_header = this->html_header();
		// 		html = html + html_header;
		// 		html_basement = this->html_basement();
		// 		path = find_path_to_html();
		// 		path = path + _request.get_page_index();
		// 		if (stat((_request.get_page_index()).c_str(), stat_file) != -1 || _request.get_page_index() == "/") // переделать под любой путь
		// 		{
		// 			if (_request.get_page_index() == "/")
		// 			{	 
		// 				_locations = _conf.get_locations();
		// 				_loc = _locations.find("/");
		// 				if (_loc != _conf.get_locations().end()) 
		// 				{
		// 					content_file = create_path_to_file(_loc->second);
		// 					// if (stat(content_file.c_str(), stat_file) != -1)
		// 						html = html + read_full_file(content_file);
		// 					// else
		// 					// 	html = create_error_page(404);
		// 				}
		// 				else
		// 				{
		// 					html = create_error_page(404);
		// 				}
		// 			}
		// 			else
		// 			{
		// 				if (S_ISREG(stat_file->st_mode))
		// 				{
		// 					content_file = read_full_file(_request.get_page_index());
		// 					html = html + content_file;
		// 				}
		// 				if (S_ISDIR(stat_file->st_mode))
		// 				{
		// 					html = html + crate_dir_tree(_request.get_page_index().c_str());
		// 				}
		// 			}
		// 		}
		// 		else
		// 		{
		// 			html = html + create_error_page(404);
		// 		}
				
		// 	}
		// 	else
		// 	{
		// 		html = html + create_error_page(error);
		// 	}
		// 	html = html + html_basement;
		// 	return (html);
		// }

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
					// std::cout << line << std::endl;
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
		
			return (body_html);
		}

		std::string error_404()
		{
			std::string body_html;
		
			return (body_html);
		}

		std::string error_501()
		{
			std::string body_html;
		
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
			std::string path_and_file;
			struct stat stat_file;
			// std::map<std::string, std::map<std::string, std::string> >::iterator it = _locations.begin();

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
						// getcwd(buf, sizeof(buf));
						// path_and_file.erase(0, 1);
						// path_and_file = buf + path_and_file;
						stat_path = path_and_file.c_str();
						if (stat(stat_path, &stat_file) != -1)
						{
							return (path_and_file);
						}
						path_and_file.clear();
						i++;
					}
				}
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

			if (file_or_path.find(".") != std::string::npos)
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

		std::string create_path_to_file(std::map<std::string, std::string> loc)
		{
			std::string path_to_file;
			std::map<std::string, std::string>::iterator it = loc.begin();
			std::map<std::string, std::string>::iterator it2 = loc.end();
			
			while (it != it2)
			{
				if (it->first == "pass")
					path_to_file = path_to_file + it->second;

				if (it->first == "index")
					path_to_file = path_to_file + it->second;
				it++;
			}//переделать бредятину
			path_to_file = "/Users/dmadelei/Documents/webserv/web_document/7000_port/html/page1.html";
			return (path_to_file);
		}
};

#endif
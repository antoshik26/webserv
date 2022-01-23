#ifndef RESPONSE_MANAGER_HPP
#define RESPONSE_MANAGER_HPP
#include <iostream>
#include <string>
#include <fstream>
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
			struct stat* stat_file = NULL;
			dir_tree = "HTTP/1.1 200 OK\r\n\r\n";
			while ((dirent_file = readdir(path)) != NULL)
			{
				if (stat(dirent_file->d_name, stat_file) != -1)
				{
					if (S_ISREG(stat_file->st_mode))
					{
						buf = "<a href=" + (std::string)dirent_file->d_name + " >" + (std::string)dirent_file->d_name + " </a>\n";
						//file S_ISREG
					}
					if (S_ISDIR(stat_file->st_mode))
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
			std::map<std::string, std::map<std::string, std::string> >::iterator _loc;
			std::map<std::string, std::map<std::string, std::string> > _locations;
			struct stat* stat_file = NULL;
			int error;

			if ((error = this->error()) == 0)
			{
				html_header = this->html_header();
				html = html + html_header;
				html_basement = this->html_basement();
				if (stat((_request.get_page_index()).c_str(), stat_file) != -1 || _request.get_page_index() == "/") // переделать под любой путь
				{
					if (_request.get_page_index() == "/")
					{	 
						_locations = _conf.get_locations();
						_loc = _locations.find("/");
						if (_loc != _conf.get_locations().end()) 
						{
							content_file = create_path_to_file(_loc->second);
							// if (stat(content_file.c_str(), stat_file) != -1)
								html = html + read_full_file(content_file);
							// else
							// 	html = create_error_page(404);
						}
						else
						{
							html = create_error_page(404);
						}
					}
					else
					{
						if (S_ISREG(stat_file->st_mode))
						{
							content_file = read_full_file(_request.get_page_index());
							html = html + content_file;
						}
						if (S_ISDIR(stat_file->st_mode))
						{
							html = html + crate_dir_tree(_request.get_page_index().c_str());
						}
					}
				}
				else
				{
					html = html + create_error_page(404);
				}
				
			}
			else
			{
				html = html + create_error_page(error);
			}
			html = html + html_basement;
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

		// std::string create_path_to_file(std::pair<std::string, std::vector<std::string> >)
		// {
		// 	std::string path_to_file;

		// 	// if ()
		// 	// {

		// 	// }
		// 	return (path_to_file);
		// }

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
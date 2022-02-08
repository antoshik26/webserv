#ifndef RESPONSE_MANAGER_HPP
#define RESPONSE_MANAGER_HPP
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include "../request_manager/request_manager.hpp"
#include "../config_parser/config_parser.hpp"
#include "../Cookies/cookies.hpp"
#include "../cgi/cgi.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include"iostream"
#include"string"
class response_manager
{
	protected:
		request_manager _request;
		config_parser _conf;
		cookies _cookies_serv;
		cgi _cgi_scripts;
		std::string response;
	public:
		response_manager()
		{

		}

		response_manager(request_manager request, config_parser conf, cookies cookies_serv, cgi cgi_scripst)
		{
			_request = request;
			_conf = conf;
			_cookies_serv = cookies_serv;
			_cgi_scripts = cgi_scripst;
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
			if (error == 501)
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
			std::string html_header = "HTTP/1.1 200 OK\r\n";
			std::map<std::string, std::string> cookies_value;
			std::map<std::string, std::string>::iterator it;
			std::map<std::string, std::string>::iterator it2;
			cookies_value = _cookies_serv.get_cookies(_conf.get_port());

			if ((!cookies_value.empty()))
			{	
				it = cookies_value.begin();
				it2 = cookies_value.end();
				while (it != it2)
				{
					html_header = html_header + "Set-Cookie:" + it->first + "=" + it->second + ";\r\n";
					it++;
				}
			}
			html_header = html_header + "\r\n";
			return(html_header);
		}

		std::string html_header(int code)
		{
			std::string html_header = "HTTP/1.1 " + std::to_string(code) + " OK\r\n\r\n";
			return(html_header);
		}

		std::string html_header(int code, std::string text)
		{
			std::string html_header = "HTTP/1.1 " + std::to_string(code) + " " + text + " OK\r\n\r\n";
			return(html_header);
		}

		std::string html_basement()
		{
			std::string html_basement = "\r\n\r\n";
			return(html_basement);
		}
		
		std::string error_403()
		{
			std::string body_html;
			// HTTP 403 Forbidden
			return (body_html);
		}

		std::string error_204()
		{
			std::string body_html;
			// 204 No Content
			return (body_html);
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

			body_html = "HTTP/1.1 307 Temporary Redirect\r\n";
			body_html = body_html + "Location: " + _conf.get_return();
			return (body_html);
		}
		//путь до html
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

		std::string find_path_to_html(std::string path_to_file)
		{
			(void)path_to_file;
			std::string asbn;
			// size_t i = 0;
		 	// const char* stat_path;
			// char buf[1000];
			// std::string path;
			// std::map<std::string, std::map<std::string, std::string> > _locations;
			// std::vector<std::string> split_file;
			// std::string path_and_file = "";
			// struct stat stat_file;
			// std::map<std::string, std::map<std::string, std::string> >::iterator it = _locations.begin();


			// _locations = path_to_file;
			// for (std::map<std::string, std::map<std::string, std::string> >::iterator it = _locations.begin(); it != _locations.end(); it++)//if path exist
			// {
			// 	if (_request.get_page_index() == it->first)//папка или файл
			// 	{
			// 		split_file = split((it->second).find("index"));
			// 		path = (it->second).find("root")->second;
			// 		while (i < split_file.size())
			// 		{
			// 			path_and_file = path + split_file[i];
			// 			stat_path = path_and_file.c_str();
			// 			if (stat(stat_path, &stat_file) != -1) //&& S_ISDIR(stat_file.st_mode)) //НЕ ПАПКА
			// 			{
			// 				return (path_and_file);
			// 			}
			// 			path_and_file.clear();
			// 			i++;
			// 		}
			// 	}
			// }
			// if (path_and_file.empty())
			// {
			// 	path = _locations.find("/")->second.find("root")->second;
			// 	if (!(_locations.find("/")->second.find("index")->second.empty()))
			// 		path_and_file = path + _request.get_page_index();
			// }
			return (asbn);
		}

		std::string find_path_to_html() //переделать
		{
			size_t i = 0;
		 	const char* stat_path;
			char buf[1000];
			std::string path;
			std::map<std::string, std::map<std::string, std::string> > _locations;
			std::vector<std::string> split_file;
			std::string file;
			std::string path_and_file = "";
			struct stat stat_file;
			std::map<std::string, std::map<std::string, std::string> >::iterator it = _locations.begin();

			_locations = _conf.get_locations();
			file = split_path_and_files(_request.get_page_index());
			// if (file.empty())
			// {

			// }
			for (std::map<std::string, std::map<std::string, std::string> >::iterator it = _locations.begin(); it != _locations.end(); it++)//if path exist
			{
				if (_request.get_page_index() == it->first)//папка или файл
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
			// std::map<std::string, std::map<std::string, std::string> > _locations;
			// std::string path=_request.get_page_index();

			// _locations = _conf.get_locations();
			// for (std::map<std::string, std::map<std::string, std::string> >::iterator it = _locations.begin(); it != _locations.end(); it++)//if path exist
			// {
			// 	if(path == it->first)
			// 	{
			// 		if(!parse_location_root(it).empty())
			// 		{
			// 			return(parse_location_root(it));
			// 		}
			// 	}
			// }
			// if (Exists(path.c_str()) || Exists(("."+path).c_str()))
			// {
			// 	return(path);
			// }
			// path.clear();
			// return(path);
		}
		
		std::string parse_location_root(std::map<std::string, std::map<std::string, std::string> >::iterator it)
		{
			std::vector<std::string> split_file = split((it->second).find("index"));
			std::string root;

			root=(it->second).find("root")->second;
			for (std::vector<std::string>::iterator it_v=split_file.begin();it_v!=split_file.end();it_v++)
			{
				if(Exists((root + *(it_v)).c_str())==1 || Exists(("."+root + *(it_v)).c_str())==1 )
				{
					return(root+*(it_v));
				}
			}
			root.clear();
			return(root);
		}

		int Exists(const char *path)
		{
    	struct stat info;

    	if(stat( path, &info ) != 0)
        	return 0;
    	else 
        	return 1;
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

		int definition_path_or_filr(std::string file_or_path) //переделать убрать
		{
			(void)file_or_path;
			int a = 0;

			if (file_or_path.find(".") != std::string::npos && file_or_path.find("html") == std::string::npos)
				a = 1;
			return a;
		}

		int definition_path_or_filr_norm(std::string file_or_path) //переделать убрать
		{
			int a = 0;
			struct stat stat_file;
			
			if (stat(file_or_path.c_str(), &stat_file ) != -1)
			{
				if (S_ISREG(stat_file.st_mode))
				{
					a = 1;
					return (a);
				}
				if (S_ISDIR(stat_file.st_mode))
				{
					a = 2;
					return (a);
				}
			}
			return a;
		}

		std::string split_path_and_files(std::string path_location)
		{
			(void)path_location;
			std::string file;
			size_t i = path_location.length();
			
			while (path_location[i] != '/')
				i--;
			file = path_location.substr(i, i - path_location.length());
			return (file);
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
					if (path.find(".py") != std::string::npos)
					{
						// cgi_py();
					}
					if (path.find(".cs") != std::string::npos)
					{
						//cgi_cs();
					}
					if (stat(path.c_str(), &stat_file) != -1)
						html = html + read_full_file(path);
					else
						html = create_error_page(404);
				}
			}
			html = html + html_basement;
			// std::cout << html << std::endl;
			return (html);
		}

		std::string metod_post()
		{
			std::ofstream f;
			std::string html;
			std::string html_header;
			std::string html_basement;
			std::string content_file;
			std::string path;
			std::string result_cgi;
			std::map<std::string, std::map<std::string, std::string> >::iterator _loc;
			std::map<std::string, std::map<std::string, std::string> > _locations;
			std::map<std::string, std::string> _body;
			struct stat stat_file;
			size_t n;

			html_basement = this->html_basement();
			//multipart
			_body = _request.get_body();
			if ((_body.find("Content-Disposition")) != _body.end())
			{
				html_header = this->html_header(204, "No Content");
				html = html + html_header;
				if ((n = _request.get_body().find("Content-Disposition")->second.find("filename")) != std::string::npos)
				{

					path = find_path_to_html();
					if (path[path.length() - 1] != '/')
						path = path + '/';
					content_file = _request.get_body().find("Content-Disposition")->second.substr(n + 10, 8);//n - _request.get_body().find("Content-Disposition")->second.find("/r") - 1);
					path = "/Users/dmadelei/Desktop/";
					path = path + content_file;
					if (!(path.empty()))
					{
						if (stat(path.c_str(), &stat_file) == 0)
						{
							f.open(path, std::ofstream::app);
							if (f.good())
							{
								f << _request.get_body_file();
								f.close();
								//204
							}
							else
								html = create_error_page(403);
						}
						else
						{
							f.open(path);
							if (f.good())
							{
								f << _request.get_body_file();
								f.close();
								//204
							}
							else
								html = create_error_page(403);
						}
					}
					else
						html = create_error_page(403);
				}
				else
					html = create_error_page(403);
			}
			//	cgi
			// if (!(body.empty()))
			// {
			// 	multipath or cgi
			// }
			// if (definition_path_or_filr(_request.get_page_index()) != 0)	//path //вынести в работу с путями
			// {
				path = find_path_to_html();
				if (path.find(".cs") != std::string::npos || path.find(".py") != std::string::npos)
				{
					_cgi_scripts.new_cgi(".py", _conf.get_cgi(), _request.get_body_cgi());
					result_cgi = _cgi_scripts.get_string();
					std::cout << result_cgi << std::endl;
					if (_body.find("Referer") != _body.end() || _body.find("Origin") != _body.end())
					{
						if (_body.find("Referer") != _body.end())
						{
							path = find_path_to_html((_body.find("Referer"))->second);
							path = "./web_document/7000_port/html/page1.html";
							html = create_html_file_with_result_cgi(path, result_cgi);
						}
						// if (_body.find("Origin") != _body.end())
						// {
						// 	path = find_path_to_html((_body.find("Origin"))->second);
						// 	path = "./web_document/7000_port/html/page1.html";
						// 	html = html + create_html_file_with_result_cgi(path, result_cgi);
						// }
					}
					else
					{

					}
				}
			// }
			html = html + html_basement;
			return (html);
		}

		std::string metod_delete()
		{
			std::ofstream f;
			std::string html;
			std::string html_header;
			std::string html_basement;
			std::string content_file;
			std::string path;
			std::map<std::string, std::map<std::string, std::string> >::iterator _loc;
			std::map<std::string, std::map<std::string, std::string> > _locations;
			std::map<std::string, std::string> body;
			struct stat stat_file;
			size_t n;

			html_basement = this->html_basement();
			path = find_path_to_html();
			if (path.empty())
			{
				path = path + content_file;
				if (stat(path.c_str(), &stat_file) == 0)
				{
					std::remove(path.c_str());
					if (!std::ifstream(path))
						html = this->html_header(204);
				}
				else
					html = create_error_page(403);
			}
			else
				html = create_error_page(403);
			html = html + html_basement;
			return (html);
		}

		std::string create_html_file_with_result_cgi(std::string path_and_file, std::string result_cgi)
		{
			(void)path_and_file;
			(void)result_cgi;
			std::string html_result;
			std::string key;
			std::string value;
			std::string html_header;
			size_t n = 0;
			size_t k = 0;
			
			html_header = "HTTP/1.1 200 OK\r\n\r\n";
			// html_header = html_header + "Location: " + path_and_file + "\r\n\r\n";
			html_result = html_header;
			html_result = html_result + read_full_file(path_and_file);
			if ((n = result_cgi.find(":")) != std::string::npos)
			{
				key = result_cgi.substr(0, n);
				std::cout << key << std::endl;
				n++;
				value = result_cgi.substr(n, result_cgi.length() - n - 1);
				std::cout << value << std::endl;
				if ((k = html_result.find("id=\"" + key + "\"")) != std::string::npos)
				{
					while (html_result[k] != '>')
						k++;
					k++;
					html_result.insert(k, value);
					std::cout << html_result << std::endl;
				}
			}
			return (html_result);
		}
};
#endif
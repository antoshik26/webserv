#include "response_to_get_request.hpp"

response_to_get_request::response_to_get_request(request_manager request, config_parser conf, cookies cookies_serv, cgi cgi_scripst) : response_manager(request, conf, cookies_serv, cgi_scripst)
{}

response_to_get_request::~response_to_get_request()
{}

std::string response_to_get_request::metod_response()
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
				if (stat(path.c_str(), &stat_file) != -1)
				{
					if (S_ISDIR(stat_file.st_mode))
						html = html + crate_dir_tree((path).c_str(), _request.get_page_index());
					else
						html = html + read_full_file(path);
				}		
				else
				{
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

std::string response_to_get_request::crate_dir_tree(const char* path_dir, std::string location)
{
	std::string dir_tree;
	std::string buf;
	// std::string path_dir2 = "/Users/dmadelei/Documents/webserv/web_document/7000_port/";
	std::cout << path_dir << std::endl;
	// std::map<std::string, std::string> body; 
	// std::string refer;
	DIR* path = opendir(path_dir);
	struct dirent* dirent_file;
	struct stat stat_file;
	dir_tree = dir_tree + "<!DOCTYPE html>\n<html>\n<body>\n";
	std::string path_file;
	
	// if (path_dir)
	// body = _request.get_body();
	// if (body.find("Referer") != body.end())
	// {
	// 	refer = body.find("Referer")->second;
	// 	refer.erase(0, 21);
	// 	refer.push_back('/');
	// }
	if (location == "/")
		location.clear();
	if (location[location.length()] != '/')
		location.push_back('/');
	while ((dirent_file = readdir(path)) != NULL)
	{
		if (path_dir[strlen(path_dir)] == '/') 
			path_file = path_dir + (std::string)(dirent_file->d_name);
		else
			path_file =  (std::string)path_dir + "/" + (std::string)(dirent_file->d_name);
		std::cout << path_file << std::endl;
		
		if (stat(path_file.c_str(), &stat_file) != -1)
		{
			if (S_ISREG(stat_file.st_mode))
			{
				buf = "<a href=\"" + location + (std::string)dirent_file->d_name + "\">" + (std::string)dirent_file->d_name + "</a>\n";
				std::cout << buf <<std::endl;
			}
			if (S_ISDIR(stat_file.st_mode))
			{
				buf = "<a href=\"" + location + (std::string)dirent_file->d_name + "\">" + (std::string)dirent_file->d_name + "</a>\n";
				std::cout << buf <<std::endl;
			}
		}
		dir_tree = dir_tree + buf;
		dir_tree = dir_tree + "<br>\n";
		buf.clear();
	}
	dir_tree = dir_tree + "</body> \n</html>\n";
	std::cout << dir_tree << std::endl;
	return (dir_tree);
}
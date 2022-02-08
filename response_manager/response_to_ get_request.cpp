#include "response_to_get_request.hpp"

response_to_get_request::response_to_get_request()
{}

response_to_get_request::response_to_get_request(request_manager request, 
		config_parser conf, cookies cookies_serv, cgi cgi_scripst) : response_manager(request, conf, cookies_serv, cgi_scripst);
{}

response_to_get_request::~response_to_get_request()
{}

std::string metod_get()
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
#include "response_to_delete_request.hpp"


response_to_delete_request::response_to_delete_request(request_manager request, 
		config_parser conf, cookies cookies_serv, cgi cgi_scripst) : response_manager(request, conf, cookies_serv, cgi_scripst)
{}

response_to_delete_request::~response_to_delete_request()
{}

std::string response_to_delete_request::metod_response()
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

	html_basement = response_manager::html_basement();
	path = find_path_to_html();
	if (!(path.empty()))
	{
		path = path + content_file;
		if (stat(path.c_str(), &stat_file) == 0)
		{
			std::remove(path.c_str());
			if (!std::ifstream(path))
				html = response_manager::html_header(204);
		}
		else
			html = create_error_page(403);
	}
	else
		html = create_error_page(403);
	html = html + html_basement;
	return (html);
}
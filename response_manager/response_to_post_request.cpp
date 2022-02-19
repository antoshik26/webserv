#include "response_to_post_request.hpp"

response_to_post_request::response_to_post_request(request_manager request, 
			config_parser conf, cookies cookies_serv, cgi cgi_scripst, session_manager database) : response_manager(request, conf, cookies_serv, cgi_scripst)
{}

response_to_post_request::~response_to_post_request()
{}

std::string response_to_post_request::metod_response()
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
	size_t j;

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
			content_file = _request.get_body().find("Content-Disposition")->second;
			n = n + 10;
			j = n;
			while (content_file[n]!= '\"')
				n++;
			std::string content_file2 = content_file.substr(j, n - j);
			std::cout << content_file2 << std::endl;
			path = "/Users/dmadelei/Desktop/";
			path = path + content_file2;
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
	else
	{
	//	cgi
	// if (!(body.empty()))
	// {
	// 	multipath or cgi
	// }
	// if (definition_path_or_filr(_request.get_page_index()) != 0)	//path //вынести в работу с путями
	// {
		path = find_path_to_cgi();
		if (path.find(".php") != std::string::npos || path.find(".py") != std::string::npos)
		{
			if (path.find(".php") != std::string::npos)
				_cgi_scripts.new_cgi(".php", _conf.get_cgi(), _request.get_body_cgi());
			else
				_cgi_scripts.new_cgi(".py", _conf.get_cgi(), _request.get_body_cgi());
			result_cgi = _cgi_scripts.get_string();
			std::cout << result_cgi << std::endl;
			if (_body.find("Referer") != _body.end() || _body.find("Origin") != _body.end())
			{
				if (_body.find("Referer") != _body.end())
				{
					path = (_body.find("Referer"))->second;
					size_t n = path.find("localhost");
					while (path[n] != '/')
						n++;
					content_file = path.substr(n, path.length() - n);
					path = find_path_to_html(content_file);
					html = create_html_file_with_result_cgi(path, result_cgi);
				}
			}
		}
		else
		{
			html = create_error_page(403);	
		}
	}
	html = html + html_basement;
	return (html);
}

std::string response_to_post_request::create_html_file_with_result_cgi(std::string path_and_file, std::string result_cgi)
{
	(void)path_and_file;
	(void)result_cgi;
	std::string html_result;
	std::string key;
	std::string value;
	std::string html_header;
	size_t n = 0;
	size_t k = 0;
	
	html_header = this->html_header(session_identifier);
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
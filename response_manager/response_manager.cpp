#include "response_manager.hpp"

response_manager::response_manager()
{

}

response_manager::response_manager(request_manager request, config_parser conf, cookies cookies_serv, cgi cgi_scripst)
{
	_request = request;
	_conf = conf;
	_cookies_serv = cookies_serv;
	_cgi_scripts = cgi_scripst;
}
//оператор копирование 
//оператор присваивания

response_manager::~response_manager()
{
}

std::string response_manager::html_header()
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

std::string response_manager::html_header(int code)
{
	std::string html_header = "HTTP/1.1 " + std::to_string(code) + " OK\r\n\r\n";
	return(html_header);
}

std::string response_manager::html_header(int code, std::string text)
{
	std::string html_header = "HTTP/1.1 " + std::to_string(code) + " " + text + " OK\r\n\r\n";
	return(html_header);
}

std::string response_manager::html_basement()
{
	std::string html_basement = "\r\n\r\n";
	return(html_basement);
}

std::vector<std::string> response_manager::split(std::map<std::string, std::string>::iterator it)
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

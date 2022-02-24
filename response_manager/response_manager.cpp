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

std::string response_manager::html_header(std::pair<std::string, std::string> session_identifier)
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
	html_header = html_header + "Set-Cookie:ID=" + session_identifier.first + ";\r\n";
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

std::string response_manager::read_full_file(std::string path_to_file)
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


std::string response_manager::find_path_to_html(std::string path_to_file)
{
	(void)path_to_file;
	std::string path;
	std::map<std::string, std::map<std::string, std::string> > _locations;
	std::vector<std::string> split_file;
	std::string path_and_file = "";
	std::string file;

	_locations = _conf.get_locations();
	file = split_path_and_files(path_to_file);
	if (file.empty())
		path = find_location_path();
	else
		path = find_location_file(path_and_file);
	return (path);
}

std::string response_manager::find_path_to_html() //не работает
{
	std::string path;
	std::map<std::string, std::map<std::string, std::string> > _locations;
	std::vector<std::string> split_file;
	std::string file;
	std::string path_and_file = "";

	_locations = _conf.get_locations();
	file = split_path_and_files(_request.get_page_index());
	if (file.empty())
		path = find_location_path();
	else
		path = find_location_file(_request.get_page_index());
	return (path);
}

// std::string response_manager::find_path_to_html() //переделать
// {
// 	size_t i = 0;
// 	const char* stat_path;
// 	std::string path;
// 	std::map<std::string, std::map<std::string, std::string> > _locations;
// 	std::vector<std::string> split_file;
// 	std::string file;
// 	std::string path_and_file = "";
// 	struct stat stat_file;

// 	_locations = _conf.get_locations();
// 	file = split_path_and_files(_request.get_page_index());
// 	// if (file.empty())
// 	// {

// 	// }
// 	for (std::map<std::string, std::map<std::string, std::string> >::iterator it = _locations.begin(); it != _locations.end(); it++)//if path exist
// 	{
// 		if (_request.get_page_index() == it->first)//папка или файл
// 		{
// 			split_file = split((it->second).find("index"));
// 			path = (it->second).find("root")->second;
// 			while (i < split_file.size())
// 			{
// 				path_and_file = path + split_file[i];
// 				stat_path = path_and_file.c_str();
// 				if (stat(stat_path, &stat_file) != -1) //&& S_ISDIR(stat_file.st_mode)) //НЕ ПАПКА
// 				{
// 					return (path_and_file);
// 				}
// 				path_and_file.clear();
// 				i++;
// 			}
// 		}
// 	}
// 	if (path_and_file.empty())
// 	{
// 		path = _locations.find("/")->second.find("root")->second;
// 		if (!(_locations.find("/")->second.find("index")->second.empty()))
// 			path_and_file = path + _request.get_page_index();
// 	}
// 	return (path_and_file);
// }


std::string response_manager::find_path_to_cgi()
{
	const char* stat_path;
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

std::string response_manager::find_path_to_cgi2()
{
	const char* stat_path;
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
			path = (it->second).find("cgi_puss")->second;
			path_and_file = path + _request.get_page_index();
			stat_path = path_and_file.c_str();
			if (stat(stat_path, &stat_file) != -1)
			{
				//исполняемый
				return (path_and_file);
			}
		}
	}
	return (path_and_file);
}


int response_manager::definition_path_or_filr(std::string file_or_path) //переделать убрать
{
	(void)file_or_path;
	int a = 0;

	if (file_or_path.find(".") != std::string::npos && file_or_path.find("html") == std::string::npos)
		a = 1;
	return a;
}

int response_manager::definition_path_or_filr_norm(std::string file_or_path) //переделать убрать
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

std::string response_manager::split_path_and_files(std::string path_location)
{
	(void)path_location;
	std::string file;
	size_t i = path_location.length();
	
	while (path_location[i] != '/')
		i--;
	file = path_location.substr(i + 1, i - path_location.length());
	return (file);
}

std::string response_manager::find_location_path()
{
	const char* stat_path;
	std::string path;
	std::map<std::string, std::map<std::string, std::string> > _locations;
	std::vector<std::string> split_file;
	std::string file;
	std::string path_and_file = "";
	std::string path_location;
	struct stat stat_file;
	size_t i = 0;

	path_location = find_firs_location(_request.get_page_index());
	_locations = _conf.get_locations();
	for (std::map<std::string, std::map<std::string, std::string> >::iterator it = _locations.begin(); it != _locations.end(); it++)//if path exist
	{
		if (path_location == it->first)//папка или файл
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
		path = _locations.find("/")->second.find("root")->second + _request.get_page_index();
		stat_path = path.c_str();
		if (stat(stat_path, &stat_file) != -1)
			return (path);
	}
	return (path);
}

std::string response_manager::find_location_file(std::string file)
{
	(void)file;
	const char* stat_path;
	std::string path;
	std::string path_location;
	std::map<std::string, std::map<std::string, std::string> > _locations;
	std::vector<std::string> split_file;
	// std::string file;
	std::string path_and_file = "";
	struct stat stat_file;

	_locations = _conf.get_locations();
	path_location = find_firs_location(_request.get_page_index());
	for (std::map<std::string, std::map<std::string, std::string> >::iterator it = _locations.begin(); it != _locations.end(); it++)//if path exist
	{
		if (path_location == it->first)//папка или файл
		{
			path = (it->second).find("root")->second;
			if (path[path.length() - 1] == '/')
				path.pop_back();
			path_and_file = path + file;
			stat_path = path_and_file.c_str();
			if (stat(stat_path, &stat_file) != -1) //&& S_ISDIR(stat_file.st_mode)) //НЕ ПАПКА
			{
				return (path_and_file);
			}
			path_and_file.clear();
		}
	}
	return (path);
}

std::string response_manager::find_firs_location(std::string path)
{
	(void)path;
	std::string location;
	size_t j = 0;
	size_t i = j;

	while (path[i] != '/')
		i++;
	if (path[i] == '/')
		location = path.substr(j, i + 1 - j);
	return (location);
}

std::string response_manager::return_page()
{
	std::string body_html;

	body_html = "HTTP/1.1 307 Temporary Redirect\r\n";
	body_html = body_html + "Location: " + _conf.get_return();
	return (body_html);
}

std::string response_manager::session_manager_add_backgraund(std::string html, std::pair<std::string, std::string> persen_database)
{
	size_t n;
	std::string collor_backgraund;
	
	if ((n = html.find("background-color")) != std::string::npos)
	{
		collor_backgraund = persen_database.second;
		html.insert(n + 17, "#");
		html.insert(n + 18, collor_backgraund);
		std::cout << html << std::endl;
	}
	return (html);
}

// std::vector<std::string> find_firs_location(std::string path)
// {
// 	(void)path;
// 	std::string location;
// 	std::vector arr_location;
// 	size_t i = 0;
// 	size_t i = j;

// 	while (path[i])
// 	{
// 		while (path[i]! = '/')
// 			i++;
// 		location = path.substr(j, j - i);
// 		arr_location.push_back(location);
// 		j = i;
// 		i++;
// 	}
// 	location = path.substr(j, j - i);
// 	arr_location.push_back(location);
// 	return(arr_location);
// }
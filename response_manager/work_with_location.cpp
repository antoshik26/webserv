#include "work_with_location.hpp"

std::string work_with_location::find_path_to_html(std::string path_to_file)
{
	(void)path_to_file;
	size_t i = 0;
	const char* stat_path;
	char buf[1000];
	std::string path;
	std::map<std::string, std::map<std::string, std::string> > _locations;
	std::vector<std::string> split_file;
	std::string path_and_file = "";
	struct stat stat_file;

	_locations = _conf.get_locations();
	file = split_path_and_files(path_to_file);
	if (file.empty())
		path = find_location_path()
	else
		path = find_location_file(file);
	return (path_and_file);
}

std::string work_with_location::find_path_to_html() //переделать
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

	_locations = _conf.get_locations();
	file = split_path_and_files(_request.get_page_index());
	if (file.empty())
		path = find_location_path()
	else
		path = find_location_file(file);
	return (path_and_file);
}

std::string work_with_location::find_path_to_cgi()
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

int work_with_location::definition_path_or_filr(std::string file_or_path) //переделать убрать
{
	(void)file_or_path;
	int a = 0;

	if (file_or_path.find(".") != std::string::npos && file_or_path.find("html") == std::string::npos)
		a = 1;
	return a;
}

int work_with_location::definition_path_or_filr_norm(std::string file_or_path) //переделать убрать
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

std::string work_with_location::split_path_and_files(std::string path_location)
{
	(void)path_location;
	std::string file;
	size_t i = path_location.length();
	
	while (path_location[i] != '/')
		i--;
	file = path_location.substr(i, i - path_location.length());
	return (file);
}

std::string work_with_location::find_location_path()
{
	size_t i = 0;
	const char* stat_path;
	char buf[1000];
	std::string path;
	std::map<std::string, std::map<std::string, std::string> > _locations;
	std::vector<std::string> split_file;
	std::string file;
	std::string path_and_file = "";
	std::string path_location;
	struct stat stat_file;

	path_location = find_firs_location(_request.get_page_index());
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
		if (stat(path, &stat_file) != -1)
			return (path);
	}
	return (path);
}

std::string work_with_location::find_location_file(std::string file)
{
	(void)file;
	size_t i = 0;
	const char* stat_path;
	char buf[1000];
	std::string path;
	std::map<std::string, std::map<std::string, std::string> > _locations;
	std::vector<std::string> split_file;
	std::string file;
	std::string path_and_file = "";
	struct stat stat_file;

	for (std::map<std::string, std::map<std::string, std::string> >::iterator it = _locations.begin(); it != _locations.end(); it++)//if path exist
	{
		if (_request.get_page_index() == it->first)//папка или файл
		{
			path = (it->second).find("root")->second;
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

std::string find_firs_location(std::string path)
{
	(void)path;
	std::string location;
	size_t j = 1;
	size_t i = j;

	while (path[i] != '/' || path[i])
		i++;
	if (path[i] = '/')
		location = path.substr(j, i - j);

}

std::vector<std::string> find_firs_location(std::string path)
{
	(void)path;
	std::string location;
	std::vector arr_location;
	size_t i = 0;
	size_t i = j;

	while (path[i])
	{
		while (path[i]! = '/')
			i++;
		location = path.substr(j, j - i);
		arr_location.push_back(location);
		j = i;
		i++;
	}
	location = path.substr(j, j - i);
	arr_location.push_back(location);
	return(arr_location);
}
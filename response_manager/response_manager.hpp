#ifndef RESPONSE_MANAGER_HPP
#define RESPONSE_MANAGER_HPP
#include <iostream>
#include <string>
#include "../request_manager/request_manager.hpp"
#include "../config_parser/config_parser.hpp"

class response_manager
{
	private:
		std::string response;

	public:
		response_manager(request_manager request, config_parser conf)
		{
			(void)request;
			(void)conf;
		}

		~response_manager()
		{
		}

		std::string crate_dir_tree(char* path_dir)
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

};

#endif
#ifndef RESPONSE_TO_GET_REQUEST_HPP
#define RESPONSE_TO_GET_REQUEST_HPP
#include "response_manager.hpp"
#include "response_error_request.hpp"
#include <map>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <cstdlib>

class response_to_get_request: public virtual response_manager, public virtual response_error_request
{
	private:
		std::pair<std::string, std::string> session_identifier;
	public:
		response_to_get_request(request_manager request, config_parser conf, cookies cookies_serv, cgi cgi_scripst, session_manager database);
		~response_to_get_request();
		std::string metod_response();
		std::string crate_dir_tree(const char* path_dir, std::string location);
};
#endif

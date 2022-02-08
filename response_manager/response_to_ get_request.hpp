#ifndef RESPONSE_TO_GET_REQUEST_HPP
#define RESPONSE_TO_GET_REQUEST_HPP
#include "response_manager.hpp"

class response_to_get_request: public response_manager, public work_with_location, public response_error_request
{
	private:

	public:
		response_to_get_request();
		response_to_get_request(request_manager request, config_parser conf, cookies cookies_serv, cgi cgi_scripst);
		~response_to_get_request();
		std::string metod_get();
		std::string crate_dir_tree(const char* path_dir);
	private:

};
#endif

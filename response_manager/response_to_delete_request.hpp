#ifndef RESPONSE_TO_DELETE_REQUEST_HPP
#define RESPONSE_TO_DELETE_REQUEST_HPP
#include "response_manager.hpp"

class response_to_delete_request: public response_manager, public work_with_location
{
	private:
		
	public:
		response_to_delete_request();
		response_to_delete_request(request_manager request, config_parser conf, cookies cookies_serv, cgi cgi_scripst);
		~response_to_delete_request();
		std::string metod_delete();
	private:
};
#endif
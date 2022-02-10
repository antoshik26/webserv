#ifndef RESPONSE_TO_POST_REQUEST_HPP
#define RESPONSE_TO_POST_REQUEST_HPP
#include "response_manager.hpp"
#include "response_error_request.hpp"

class response_to_post_request: public virtual response_manager, public virtual response_error_request
{
	public:
		response_to_post_request(request_manager request, config_parser conf, cookies cookies_serv, cgi cgi_scripst);
		~response_to_post_request();
		std::string metod_response();
		std::string create_html_file_with_result_cgi(std::string path_and_file, std::string result_cgi);
};
#endif
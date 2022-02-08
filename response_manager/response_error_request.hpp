#ifndef RESPONSE_ERROR_REQUEST_HPP
#define RESPONSE_MANAGER_HPP
#include "response_error_request.hpp"

class response_error_request
{
	private:

	public:
		response_error_request();
		~response_error_request();
		std::string create_error_page(int error);
		std::string error_403();
		std::string error_204();
		std::string return_page();
	private:

};
#endif
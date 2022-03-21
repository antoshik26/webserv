#ifndef RESPONSE_ERROR_REQUEST_HPP
#define RESPONSE_ERROR_REQUEST_HPP
#include <string>

class response_error_request
{
	public:
		std::string create_error_page(int error);
		std::string error_403();
		std::string error_204();
		std::string error_500();
		std::string error_404();
		std::string error_501();
};
#endif
#include "response_error_request.hpp"

std::string response_error_request::create_error_page(int error)
{
	std::string html_error;
	if (error == 500)
		html_error = this->error_500();
	if (error == 404)
		html_error = this->error_404();
	if (error == 501)
		html_error = this->error_501();
	return (html_error);
}

std::string response_error_request::error_403()
{
	std::string body_html;
	// HTTP 403 Forbidden
	return (body_html);
}

std::string response_error_request::error_204()
{
	std::string body_html;
	// 204 No Content
	return (body_html);
}


std::string response_error_request::error_500()
{
	std::string body_html;

	body_html = "HTTP/1.1 500 Internal Server Error\r\n\r\n";
	body_html = body_html + "<!DOCTYPE html>";
	body_html = body_html + "<html>";
	body_html = body_html + "<body>";
	body_html = body_html + "<h1>500</h1>";
	body_html = body_html + "</body>";
	body_html = body_html + "</html>";
	// body_html = body_html + html_basement();
	return (body_html);
}

std::string response_error_request::error_404()
{
	std::string body_html;

	body_html = "HTTP/1.1 404 Not Found\r\n\r\n";
	body_html = body_html + "<!DOCTYPE html>";
	body_html = body_html + "<html>";
	body_html = body_html + "<body>";
	body_html = body_html + "<h1>404</h1>";
	body_html = body_html + "</body>";
	body_html = body_html + "</html>";
	// body_html = body_html + html_basement();
	return (body_html);
}

std::string response_error_request::error_501()
{
	std::string body_html;
	
	body_html = "HTTP/1.1 501 Not Implemented\r\n\r\n";
	body_html = body_html + "<!DOCTYPE html>";
	body_html = body_html + "<html>";
	body_html = body_html + "<body>";
	body_html = body_html + "<h1>501</h1>";
	body_html = body_html + "</body>";
	body_html = body_html + "</html>";
	// body_html = body_html + html_basement();
	return (body_html);
}

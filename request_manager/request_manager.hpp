#ifndef REQUEST_MANAGER_HPP
#define REQUEST_MANAGER_HPP
#include <map>
#include <string>
#include <vector>
#include <iostream>

class request_manager
{
	private:
		std::string _name_request;
		std::string _name_protocol;
		std::string _page;
		std::string _page_and_param;
		std::string _page_index;
		std::string _body_file;
		// std::map<std::string, std::vector<std::string> > _body;
		std::map<std::string, std::string> _body;
		std::map<std::string, std::string> _body_cgi;
		std::map<std::string, std::string> _cooci;
		std::map<std::string, std::string> _parser_cookies;
	public:
		request_manager()
		{
		}
	
		request_manager(std::string request)
		{
			(void)request;

			find_method_http(request);
			find_page_and_param(request);
			find_protocol(request);
			parsing_request(request);
			parsing_body(request);
		}
		//оператор копирование 
		//оператор присваивания

		std::string get_name_request()
		{
			return (_name_request);
		}

		std::string get_name_protocol()
		{
			return (_name_protocol);
		}

		std::string get_page_and_param()
		{
			return (_page);
		}

		std::string get_page_index()
		{
			return (_page_index);
		}

		std::map<std::string, std::string> get_body()
		{
			return (_body);
		}
		std::map<std::string, std::string> get_body_cgi()
		{
			return (_body_cgi);
		}

		std::string get_body_file()
		{
			return (_body_file);
		}

		~request_manager()
		{

		}

	private:
		void find_method_http(std::string request)
		{
			_name_request = "";
			if (request.find("GET") != std::string::npos)
			{
				_name_request = "GET";
				return;
			}
			if (request.find("POST") != std::string::npos)
			{
				_name_request = "POST";
				return;
			}
			if (request.find("DELETE") != std::string::npos)
			{
				_name_request = "DELETE";
				return;
			}
		}

		void find_protocol(std::string request)
		{
			_name_protocol = "";
			if (request.find("HTTP/1.1") != std::string::npos)
			{
				_name_protocol = "HTTP/1.1";
				return;
			}
		}

		void parsing_request(std::string request)
		{
			std::pair<std::string, std::string> pair_node;

			pair_node = find_line(request, "Host", ':');
			//проверка
			_body.insert(pair_node);
			pair_node = find_line(request, "Connection", ':');
			//проверка
			_body.insert(pair_node);
			pair_node = find_line(request, "sec-ch-ua", ':');
			//проверка
			_body.insert(pair_node);
			pair_node = find_line(request, "sec-ch-ua-mobile", ':');
			//проверка
			_body.insert(pair_node);
			pair_node = find_line(request, "sec-ch-ua-platform", ':');
			//проверка
			_body.insert(pair_node);
			pair_node = find_line(request, "Upgrade-Insecure-Requests", ':');
			//проверка
			_body.insert(pair_node);
			pair_node = find_line(request, "User-Agent", ':');
			//проверка
			_body.insert(pair_node);
			pair_node = find_line(request, "Accept", ':');
			//проверка
			_body.insert(pair_node);
			pair_node = find_line(request, "Sec-Fetch-Site", ':');
			//проверка
			_body.insert(pair_node);
			pair_node = find_line(request, "Sec-Fetch-Mode", ':');
			//проверка
			_body.insert(pair_node);
			pair_node = find_line(request, "Sec-Fetch-User", ':');
			//проверка
			_body.insert(pair_node);
			pair_node = find_line(request, "Accept-Encoding", ':');
			//проверка
			_body.insert(pair_node);
			pair_node = find_line(request, "Accept-Language", ':');
			//проверка
			_body.insert(pair_node);
			pair_node = find_line(request, "Transfer-Encoding", ':');
			_body.insert(pair_node);
			//проверка
			pair_node = find_line(request, "Content-Length", ':');
			_body.insert(pair_node);
			//post
			pair_node = find_line(request, "Cache-Control", ':');
			_body.insert(pair_node);

			pair_node = find_line(request, "Origin", ':');
			_body.insert(pair_node);

			pair_node = find_line(request, "Content-Type", ':');
			_body.insert(pair_node);

			pair_node = find_line(request, "Referer", ':');
			_body.insert(pair_node);

			pair_node = find_line(request, "Content-Disposition", ':');
			_body.insert(pair_node);

			pair_node = find_line(request, "Content-Type", ':');
			_body.insert(pair_node);
			parsing_cookies(request);
		}

		void find_page_and_param(std::string request)
		{
			(void)request;
			std::string page;
			std::string line;
			size_t i = 0;
			size_t j = 0;

			i = request.find("/");
			j = request.find("HTTP");
			line = request.substr(i, ((j - i) - 1));
			_page_and_param = line;
			if ((i = line.find("?")) != std::string::npos)
			{
				parsing_param(line.substr(i, (j - 1)));
			}
			_page_index = line;
		}

		void parsing_body(std::string body)
		{
			std::string line_body;
			std::string str;
			std::string boundary;
			size_t n = 0;
			size_t i = 0;
			
			if (_name_request == "GET")
			{
				while (body[i] != '\n')
					i++;
				str = body.substr(0, i);
				if ((n = str.find('?')) != std::string::npos)
				{
					i = n;
					while (str[n] != ' ')
						n++;
					line_body = str.substr(i, n - i);
					split_param_body(line_body);
				}
			}
			if (_name_request == "POST")
			{
				if ((n = body.find("Content-Disposition")) != std::string::npos)
				{
					i = body.find("Content-Type:");
					i = body.find("Content-Type:", i + 1);
					while (body[i] != '\n')
						i++;
					n = body.find("Content-Type: multipart/form-data; boundary=");
					boundary = body.substr(n);
					n = boundary.find("\r\n") - 45;
					boundary = "---" + boundary.substr(45, n) + "--";
					n = body.find(boundary);
					_body_file = body.substr((i + 3), n - (i + 3));
				}
				else
				{
					n = body.length();
					i = n;
					while (body[i] != '\n')
						i--;
					str = body.substr(i + 1, n - i);
					split_param_body(str);
				}	
			}
			if (_name_request == "DELETE")
			{
				
			}
		}

		void parsing_page_index(std::string body_srt)
		{
			(void)body_srt;
		}

		void split_param_body(std::string body_srt)
		{
			std::string page_and_param;
			
			if (!(_body_cgi.empty()))
				_body_cgi.clear();
			parsing_param(body_srt);
			// _page_and_param = page_and_param;
		}

		void parsing_param(std::string body)
		{
			(void)body;
			std::pair<std::string, std::string> obj_map;
			int i = 0;
			int j = 0;

			while (body[i])
			{
				if (body[i] == '=')
				{
					obj_map.first = body.substr(j, i - j);
					j = i + 1;
				}
				if (body[i] == '&')
				{
					obj_map.second = body.substr(j, i - j);
					j = i + 1;
					_body_cgi.insert(obj_map);
					obj_map.first.clear();
					obj_map.second.clear();
				}
				i++;
			}
			obj_map.second = body.substr(j, i - j);
			_body_cgi.insert(obj_map);
		}

		std::pair<std::string, std::string> find_line(std::string request, std::string find_string, char reg)
		{
			std::pair<std::string, std::string> *str = new std::pair<std::string, std::string>();
			size_t n;
			size_t i = 0;

			if ((n = request.find(find_string)) != std::string::npos)
			{
				i = n;
				while (request[i] != reg)
					i++;
				str->first = request.substr(n, i - n);
				i++;
				n = i;
				while (request[i] != '\r')
					i++;
				str->second = request.substr(n + 1, i - n - 1);
			}
			return (*str);
		}

		std::vector<std::string> split(std::string str, char reg)
		{
			std::vector<std::string> res_split;
			std::string item;
			int i = 0;
			int j = 0;
			for (size_t k = 0; k < str.length(); k++)
			{
				if (str[k] == reg)
				{
					res_split.push_back(str.substr(i, j));
					i = j;
					j = 0;
				}
				j++;
			}
			return (res_split);
		}

		void parsing_cookies(std::string request)
		{
			(void)request;
			// size_t n;
			// std::pair<std::string, std::string> pair_node;
			// pair_node = find_line(request, "Content-Disposition", ':');
			// std::string cookies_content;
			// if ((!pair_node->second.empty()))
			// {
			// 	cookies_value = pair_node->second;
				
			// }//доделать
		}
};

#endif

// GET / HTTP/1.1
// Host: localhost:8000
// Connection: keep-alive
// sec-ch-ua: " Not A;Brand";v="99", "Chromium";v="96", "Google Chrome";v="96"
// sec-ch-ua-mobile: ?0
// sec-ch-ua-platform: "macOS"
// Upgrade-Insecure-Requests: 1
// User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.55 Safari/537.36
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
// Sec-Fetch-Site: none
// Sec-Fetch-Mode: navigate
// Sec-Fetch-User: ?1
// Sec-Fetch-Dest: document
// Accept-Encoding: gzip, deflate, br
// Accept-Language: en-US,en;q=0.9,ru;q=0.8


// GET / HTTP/1.1
// Host: localhost:8000
// Upgrade-Insecure-Requests: 1
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
// User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_6) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/14.1.2 Safari/605.1.15
// Accept-Language: en-us
// Accept-Encoding: gzip, deflate
// Connection: keep-alive

// GET /page1?name=asdfg&sname=sdfghjgfds HTTP/1.1
// Host: localhost:8000
// Connection: keep-alive
// sec-ch-ua: " Not A;Brand";v="99", "Chromium";v="96", "Google Chrome";v="96"
// sec-ch-ua-mobile: ?0
// sec-ch-ua-platform: "macOS"
// Upgrade-Insecure-Requests: 1
// User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.55 Safari/537.36
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
// Sec-Fetch-Site: none
// Sec-Fetch-Mode: navigate
// Sec-Fetch-User: ?1
// Sec-Fetch-Dest: document
// Accept-Encoding: gzip, deflate, br
// Accept-Language: en-US,en;q=0.9,ru;q=0.8

// Transfer-Encoding: Chunked

// POST / HTTP/1.1
// Host: localhost:7000
// Connection: keep-alive
// Content-Length: 34
// Cache-Control: max-age=0
// sec-ch-ua: " Not A;Brand";v="99", "Chromium";v="96", "Google Chrome";v="96"
// sec-ch-ua-mobile: ?0
// sec-ch-ua-platform: "macOS"
// Upgrade-Insecure-Requests: 1
// Origin: http://localhost:7000
// Content-Type: application/x-www-form-urlencoded
// User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.55 Safari/537.36
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
// Sec-Fetch-Site: same-origin
// Sec-Fetch-Mode: navigate
// Sec-Fetch-User: ?1
// Sec-Fetch-Dest: document
// Referer: http://localhost:7000/
// Accept-Encoding: gzip, deflate, br
// Accept-Language: en-US,en;q=0.9,ru;q=0.8

// username=antoshik_26&password=asdf


// POST /page2.html HTTP/1.1
// Host: localhost:7000
// Connection: keep-alive
// Content-Length: 45974
// Cache-Control: max-age=0
// sec-ch-ua: " Not A;Brand";v="99", "Chromium";v="96", "Google Chrome";v="96"
// sec-ch-ua-mobile: ?0
// sec-ch-ua-platform: "macOS"
// Upgrade-Insecure-Requests: 1
// Origin: http://localhost:7000
// Content-Type: multipart/form-data; boundary=----WebKitFormBoundary8TvEWtftHp0oAjwe
// User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.55 Safari/537.36
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
// Sec-Fetch-Site: same-origin
// Sec-Fetch-Mode: navigate
// Sec-Fetch-User: ?1
// Sec-Fetch-Dest: document
// Referer: http://localhost:7000/page2.html
// Accept-Encoding: gzip, deflate, br
// Accept-Language: en-US,en;q=0.9,ru;q=0.8

// Content-Disposition: form-data; name="f"; filename="kianu.jpeg"
// Content-Type: image/jpeg
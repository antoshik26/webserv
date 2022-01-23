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
		// std::map<std::string, std::vector<std::string> > _body;
		std::map<std::string, std::string> _body;
		std::map<std::string, std::string> _body_cgi;
	public:
		request_manager()
		{
		}
	
		request_manager(std::string request)
		{
			(void)request;
			std::string line_request;

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
			//проверка
			_body.insert(pair_node);
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
			(void)body;
			split_param_body(body);
		}

		void parsing_page_index(std::string body_srt)
		{
			(void)body_srt;
		}

		void split_param_body(std::string body_srt)
		{
			(void)body_srt;
			std::string page_and_param;

			if (!(_body_cgi.empty()))
				_body_cgi.clear();
			parsing_param(body_srt);
			_page_and_param = page_and_param;
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
					obj_map.first = body.substr(j, i);
					j = i;
				}
				if (body[i] == '&' || body[i + 1] == 0)
				{
					obj_map.second = body.substr(j, i);
					j = i;
					_body.insert(obj_map);
					obj_map.first.clear();
					obj_map.second.clear();
				}
				i++;
			}
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
				str->second = request.substr(n + 1, i - n);
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
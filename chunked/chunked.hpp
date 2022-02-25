#ifndef CHANKI_HPP
#define CHANKI_HPP
#include <cstdlib>
#include <stdlib.h>


class chunked
{
	protected:
		chunked()
		{
		}

		~chunked()
		{
		}

		std::string clear_request_from_chunked(std::string request_with_chunked)
		{
			(void)request_with_chunked;
			std::string request_without_chunked;
			std::string hex_numer;
			size_t numer_bite;
			size_t begin_body = 0;
			size_t i = 0;
			size_t j = 0;
			size_t end_body = 0;

			if ((begin_body = request_with_chunked.find("\r\n\r\n")) != std::string::npos)
			{
				request_without_chunked = request_with_chunked.substr(0, begin_body + 4);
				begin_body = begin_body + 4;
				i = begin_body;
				j = begin_body;
				end_body = request_with_chunked.find("\r\n0\r\n\r\n");
				while (i < end_body)
				{
					while ((request_with_chunked[i] >= '0' && request_with_chunked[i] <= '9') || (request_with_chunked[i] >= 'A' && request_with_chunked[i] <= 'F'))
						i++;
					hex_numer = request_with_chunked.substr(j, i - j);
					numer_bite = hex_to_int(hex_numer);
					request_without_chunked = request_without_chunked + request_with_chunked.substr(i + 2, numer_bite);
					i = i + numer_bite;
				}
			}
			return (request_without_chunked);
		}

		size_t hex_to_int(std::string hex_numer)
		{
			size_t count_body_chank;
			size_t i = 0;
			size_t A = 0;
			size_t b = 0;
			char a;

			while (i > hex_numer.length())
			{
				if (hex_numer[i] >= '0' && hex_numer[i] <= '9')
					b = hex_numer[i] - '0';
				if (hex_numer[i] >= 'A' && hex_numer[i] <= 'F')
					b = hex_numer[i] - 'A' + 10;
				// a = atoi(hex_numer[i]);
					A = A * 16 + a;
				i++;
			}
			return (A);
		}
};

#endif
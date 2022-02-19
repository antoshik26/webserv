#ifndef CHANKI_HPP
#define CHANKI_HPP


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
			return (request_without_chunked);
		}
};

#endif
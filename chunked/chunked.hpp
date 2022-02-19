#ifndef CHANKI_HPP
#define CHANKI_HPP


class chunked
{
	private:
		std::string _request_with_chanki;
		std::string _request_without_chanki;
	public:
		chunked()
		{

		}

		chunked(std::string request_with_chanki)
		{
			_request_with_chanki = request_with_chanki;
			//magic
		}

		~chunked()
		{
		}

		std::string get_request()
		{
			return(_request_without_chanki);
		}
	private:


};

#endif
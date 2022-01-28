#ifndef CHANKI_HPP
#define CHANKI_HPP


class chanki
{
	private:
		std::string _request_with_chanki;
		std::string _request_without_chanki;
	public:
		chanki()
		{

		}

		chanki(std::string request_with_chanki)
		{
			_request_with_chanki = request_with_chanki;
			//magic
		}

		~chanki()
		{
		}

		std::string get_request()
		{
			return(_request_without_chanki);
		}
	private:


};

#endif
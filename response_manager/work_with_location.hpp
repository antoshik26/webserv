#ifndef WORK_WITH_LOCATION_HPP
#define WORK_WITH_LOCATION_HPP
#include "response_manager.hpp"

class work_with_location
{
	private:

	public:
		work_with_location();
		~work_with_location();
		std::string find_path_to_html(std::string path_to_file);
		std::string find_path_to_html();
		std::string find_path_to_cgi();
		int definition_path_or_filr(std::string file_or_path);
		int definition_path_or_filr_norm(std::string file_or_path);
		std::string split_path_and_files(std::string path_location);
	private:
};
#endif

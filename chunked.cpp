#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

void removeStr(std::string& str)
{
    for (std::string::iterator it = str.begin(); it != str.end(); it++)
    {   
        std::string::iterator begin = it;
        while (it != str.end() && !(str.find("0\r\n") || str.find("\r\n")))
            it++;
        if (it - begin > 1)
            it = str.erase(begin + 1, it) - 1;
    }
}

// int main()
// {
//     std::string http_chunk_header = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nchunk 2\r\n0\r\n";
//     removeStr(http_chunk_header);
//     std::cout << http_chunk_header;
//     return (0);
// }
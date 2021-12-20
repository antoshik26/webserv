#ifndef METHOD_HPP
# define METHOD_HPP
#include <iostream>
#include <map>
#include<array>
#include <sstream>
#include <string>

#define A "Accept"
#define AC "Accept-Charset"
#define AE "Accept-Encoding"
#define AL "Accept-Language"
#define Auth "Authorization"
#define Expect "Expect"
#define From "From"
#define Host "Host"
#define IfMat "If-Match"
#define IfMod "If-Modified-Since"
#define IfNMat "If-None-Match"
#define IfR "If-Range"
#define IfUMod "If-Unmodified-Since"
#define MaxF "Max-Forwards"
#define size_headers 4
#define SPACE 32
#define ERROR 1
#define OK 0
class method{
    public:
        method();
        std::map<std::string,std::string> headers;
    private:
        std::string path;
        void methodGet();
        void methodPost();
        void methodDelete();
        std::array<std::string,4> all_headers={A,AC,AE,AL};
        std::array<std::string,3> names={"GET","POST","DELETE"};
        void fill();
        int parse_body();
        int parse_headers();
        std::string name;
        std::string path;
};
#endif

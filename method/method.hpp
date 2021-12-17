#ifndef METHOD_HPP
# define METHOD_HPP
class method{
    public:
        method(&config);
    private:
        std::string path;
        void methodGet();
        void methodPost();
        void methodDelete();
};
#endif

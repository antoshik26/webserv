NAME = webserv
CC = clang++
FLAGS = -Wall -Wextra -Werror -std=c++98
INCLUDE = -I.
HEADER =  ${VECTOR}/Vector.hpp ${VECTOR}/ReversIteratorVector.hpp ${STACK}/Stack.hpp ${Stack}/IteratorVector.hpp ${MAP}/Map.hpp
SRCS = main.cpp ./cgi/cgi.cpp ./cgi/parse_cgi.cpp

OBJS = ${SRCS:.cpp=.o}

%.o: %.cpp
		${CC} -g ${FLAGS} -o ${INCLUDE} -c $< -o ${<:.cpp=.o}

all:	${NAME}

${NAME}:	${OBJS}
				${CC} -g ${FLAGS} ${INCLUDE} -o ${NAME} ${OBJS}

test:			
				${CC} -g main.cpp ./cgi/cgi.cpp ./cgi/parse_cgi.cpp ./response_manager/response_error_request.cpp ./response_manager/response_manager.cpp ./response_manager/response_to_delete_request.cpp ./response_manager/response_to_get_request.cpp ./response_manager/response_to_post_request.cpp

pusk:
			./webserv config.conf

clean:
				-rm -rf ${OBJS}

fclean:
				-rm -rf ${OBJS} ${NAME}

re:				fclean all

.PHONY:
				all clean fclean re test
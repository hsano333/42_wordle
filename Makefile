NAME := wordle

CC := g++
CFLAG := -Wall -Wextra -Werror
RM := rm
RM_FLAG := -rf

SRCS := main.cpp

OBJS := ${SRCS:%.cpp=%.o}

all : ${NAME}

${NAME} : ${OBJS}
	${CC} ${CFLAG} ${OBJS} -o ${NAME}

%.o : %.cpp
	${CC} ${CFLAG}  $^ -c -o $@

clean :
	${RM} ${RM_FLAG} ${OBJS}

fclean : clean
	${RM} ${RM_FLAG} ${NAME}

re : fclean all

test : ${NAME}
	./${NAME}

.PHONY: all clean fclean re
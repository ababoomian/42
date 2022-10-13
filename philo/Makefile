FLAGS= -Wall -Wextra -Werror
CC= gcc
NAME= philo
SRCS= $(wildcard *.c)
RM= rm -rf
OBJS= $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(FLAGS) -I. -c $< -o $@

all:$(NAME)

$(NAME):$(OBJS)
	$(CC) ${FLAGS} ${OBJS} -o ${NAME}


fclean :
	$(RM) $(NAME) $(OBJS) ~/Library/Caches

re : fclean all

.PHONY: all clean fclean re
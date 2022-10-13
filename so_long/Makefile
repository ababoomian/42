
FLAGS= -Wall -Wextra -Werror
CC= gcc
NAME= so_long
SRCS= $(wildcard *.c)
RM= rm -f
OBJS		= $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -I. -Imlx -c $< -o $@

all:$(NAME)

$(NAME):$(OBJS)
	$(CC) ${FLAGS} ${OBJS} -L. -l mlx -framework OpenGL -framework AppKit -o ${NAME}


fclean :
	$(RM) $(NAME) $(OBJS)

re : fclean all

.PHONY: all clean fclean re
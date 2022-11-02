FLAGS= -Wall -Wextra -Werror -I.
CC= cc
NAME= minishel
TEST= test
SRCS= $(wildcard *.c)
SRCS_MAIN = test.c
SRCS_OTHER = $(filter-out $(SRCS_MAIN), $(SRCS))
RM= rm -rf
OBJS= $(SRCS_OTHER:.c=.o)
OBJS_TEST= $(filter-out main.o, $(OBJS))
OBJS_TEST += $(SRCS_MAIN:.c=.o)
LINKERS= -lreadline
%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

all:$(NAME)

$(NAME):$(OBJS)
	$(CC) ${FLAGS} -o ${NAME} ${OBJS} $(LINKERS)

$(TEST): $(OBJS_TEST)
	$(CC) $(FLAGS) -o $(TEST) $(OBJS_TEST) $(LINKERS)
	

fclean :
	$(RM) $(NAME) $(OBJS) ~/Library/Caches

re : fclean all

.PHONY: all clean fclean re
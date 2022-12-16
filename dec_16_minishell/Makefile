CFLAGS= -Wall -Wextra -Werror -I./readline_arbaboom/include #-fsanitize=address -g
CC= cc
NAME= minishell
TEST= test
SRCS= $(wildcard *.c)
SRCS_MAIN = test.c
SRCS_OTHER = $(filter-out $(SRCS_MAIN), $(SRCS))
RM= rm -rf
OBJS= $(SRCS_OTHER:.c=.o)
OBJS_TEST= $(filter-out main.o, $(OBJS))
OBJS_TEST += $(SRCS_MAIN:.c=.o)
LINKERS= -L./readline_arbaboom/lib -lreadline
RD= $(shell find ${HOME} -name readline_arbaboom 2>/dev/null)
FORCE = $(SRCS) Makefile $(wildcard *.h)

all:$(NAME)

$(NAME):$(OBJS)
	$(CC) ${CFLAGS} -o ${NAME} ${OBJS} $(LINKERS)
	 mkdir -p obj && mv *.o obj

$(TEST): $(OBJS_TEST)
	$(CC) $(CFLAGS) -o $(TEST) $(OBJS_TEST) $(LINKERS)

install:
	cd readline-master && make clean && ./configure --prefix=$(RD) && make && make install

fclean :
	$(RM) $(NAME) $(OBJS) obj ~/Library/Caches/*

re : fclean all

.PHONY: all clean fclean re

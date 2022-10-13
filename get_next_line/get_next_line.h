#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H


#include <stdlib.h>
//#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

typedef struct  s_list
{
    char            *content;
    struct s_list   *next;
}               t_list;

void add_to_stash(t_list *stash, char *buf, int readed);
int is_newline(t_list *stash);
t_list *ft_lstlast(t_list *stash);
void add_to_stash(t_list *stash, char *buff, int readed);
void extract_line(t_list *stash, char **line);
void generate_line(char **line,t_list *stash);
void clean_stash(t_list **stash);
int ft_strlen(const char *str);
void free_stash(t_list  *stash);
void    ft_stash(int fd, t_list  **stash, int *read_ptr);
char *get_next_line(int fd);
#endif
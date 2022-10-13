#ifndef MINISHEL_H
# define MINISHEL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_table
{
	char	*path;
	char	*pwd;
	char 	**prc;
	char	**env;
}			t_table;

char	**ft_split(char *s, char c);
size_t ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char const *s2);
# endif
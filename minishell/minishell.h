#ifndef MINISHEL_H
# define MINISHEL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <fcntl.h>
# include <signal.h>

# define CYELLOW "\001\e[0;31m\002"
# define RESET   "\001\e[0m\002"
# define GREEN	"\e[01;32m"
# define LINE  "\001\e[0;31m\002😎minishell->"
# define OUTFILE ">"
# define INFILE "<"
# define HEARDOCK "<<"
# define APPEND ">>"

typedef struct s_dict {
	char				*key;
	char				*value;
	struct s_dict 		*next;
}						t_dict;

typedef struct	s_env
{
	char	*key;
	char	*value;
	int 	del;
	struct s_env *next;
}			t_env;

typedef struct s_table
{
	char	*token;
	char	*pwd;
	char	**path;
	char 	**prc;
	char	**cmd;
	char	**env;
	char	*test;
	char	*home;
}			t_table;

typedef struct s_main
{
	t_table	*table;

}			t_main;


typedef struct s_nodes
{
	char		**heardock;
	char		**infile;
	char		**outfile;
	char		**cmd;
	char		*rd_line;
	struct s_nodes *next;
}			t_nodes;



void		ft_getenv(char **env);
void 		cd(t_table *tab,char **read_line);
void 		execution(t_table *tab,char *line,char **env,t_env *tenv);
void 		built_in(char **read_lide,char **env,t_table *tab, t_env **tenv);
int 		ft_exit(char **read_line);
int		 	is_digit(char *str);
int		 	if_built_in(char *str);
int 		acc(t_table *tab,char *test);
int 		mat_len(char **str);
int 		ft_abs(long i);
int 		ft_isdigit(char c);
long		ft_atoi(const char *str);
char 		*epur_str(char *str);
char		*ft_strjoin(char *s1, char const *s2);
char		**ft_split(char *s, char c);
size_t		ft_strlen(const char *s);
t_table		*create_table(char **env);
void 		ft_echo(char **line,t_table *tab);
char		**ft_smart_split(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
void 		print_list(t_dict *head);
char 		*get_key_env(char *env);
char		*get_value_env(char *env);
t_dict		*new_dict(char *key, char *value);
t_dict		*init_dict(char **env);
void		print_nodes(t_nodes *head);
void 		cd(t_table *tab,char **read_line);
char		*parsed_str_lst(char *str);
t_nodes		*new_nodes( int i,char **mx);
t_nodes		*init_nodes(char **mx);
int			is_heardock(char a, char b, char c);
int			is_append(char a, char b, char c);
int			is_infile(char a, char b);
int			is_outfile(char a, char b);
int			metacheck(char a, char b, char c);
int			hd_count(char *str);
void print_list_tenv(t_env *head);
t_env	*init_env_tenv(char **env);
t_env	*new_dict_tenv(char *key, char *value);
void  ft_unset(t_env **head,char *key);
int		ft_strnequ(char const *s1, char const *s2, int n);
char	*ft_strstr(const char *haystack, const char *needle);
void multi_unset(t_env **tenv,char **read_line);
void ft_main_export(t_env **tenv,char **read_line);
void ft_export(t_env **head,char **rd);
# endif
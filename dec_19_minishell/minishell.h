/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaboom <arbaboom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 03:06:29 by vrsargsy          #+#    #+#             */
/*   Updated: 2022/12/07 20:38:44 by arbaboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <limits.h>
# include <fcntl.h>
# include <signal.h>

# define VARS
# define CYELLOW "\001\e[0;31m\002"
# define RESET   "\001\e[0m\002"
# define GREEN	"\e[01;32m"
# define LINE  "\001\e[0;31m\002😎minishell->"
# define OUTFILE ">"
# define INFILE "<"
# define HEARDOCK "<<"
# define APPEND ">>"
# define CMD 0
//Regular underline text
# define UBLK "\e[4;30m"
# define URED "\e[4;31m"
# define UGRN "\e[4;32m"
# define UYEL "\e[4;33m"
# define UBLU "\e[4;34m"
# define UMAG "\e[4;35m"
# define UCYN "\e[4;36m"
# define UWHT "\e[4;37m"

//Regular background
# define BLKB "\e[40m"
# define REDB "\e[41m"
# define GRNB "\e[42m"
# define YELB "\e[43m"
# define BLUB "\e[44m"
# define MAGB "\e[45m"
# define CYNB "\e[46m"
# define WHTB "\e[47m"

typedef enum s_types
{
	_EXTERNAL = 0, // text
	_SPACE = 1, // space
	_RED_IN = 2, // < redirection input
	_RED_OUT = 3, // > redirection output
	_PIPE = 4, // | pipe
	_EXPRESSION = 5, // $ expression
	_SINGLE_QUOTE = 6, // ' quote
	_DUBLE_QUOTE = 7, // " double qoute
	_HEREDOC = 8, // << heredoc
	_APPEND = 9, // >> append
	_UNDEFINED = 10, // ; ` doesn't handle
	_CMD = 11, // comands
	_EXPANSION_SINGLE = 12, // [ '...' ]
	_EXPANSION_DUBLE = 13, // [ "..." ]
	_DELIMITER = 14, // redirection filename
}			t_types;


typedef	struct s_token
{
	int					index;
	int					type;
	char				*token;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct	s_addres
{
	int				exit_status;
	int				descriptor;
	int				pipe_count;
	int				shlvl;
	t_token			*token;
}				t_addres;

typedef struct s_dict
{
	char				*key;
	char				*value;
	struct s_dict		*next;
}						t_dict;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				del;
	struct s_env	*next;
}					t_env;

typedef struct s_table
{
	char	*token;
	char	*pwd;
	char	**path;
	char	**prc;
	char	**cmd;
	char	**env;
	char	*test;
	char	*home;
}			t_table;

typedef struct s_main
{
	t_table	*table;
}			t_main;

typedef struct s_tok
{
	int type;
	int syntax_err;
	int delim;
	char *data;
	struct s_tok *next;

}t_tok;

typedef struct s_nodes
{
	int				pid;
	int				input;
	int				output;
	int				index;
	int				append_count;
	int				heredoc_count;
	int				infile_count;
	int				outfile_count;
	int				*redir_cnt;
	char			**append;
	char			**heardock;
	char			**redir;
	char			**infile;
	char			**outfile;
	char			**cmd;
	char			*rd_line;
	char			*syntax_err;
	t_token			*tok;
	struct s_nodes	*next;
}					t_nodes;

void		ft_getenv(char **env);
void		cd(t_env **tab, char **read_line);
void		execution(t_nodes *nds, char **env, t_env *tenv);
void		built_in(t_nodes *nds, char **read_lide, char **env, t_env **tenv);
int			ft_exit(char **read_line);
int			is_digit(char *str);
int			if_built_in(char *str);
char		*acc(char *cmd, t_env *tenv);
int			mat_len(char **str);
int			ft_abs(long i);
int			ft_isdigit(char c);
long		ft_atoi(const char *str);
char		*epur_str(char *str);
char		*ft_strjoin(char *s1, char const *s2);
char		**ft_split(char *s, char c);
size_t		ft_strlen(const char *s);
t_table		*create_table(char **env);
void		ft_echo(char **line, t_env *tab);
char		**ft_smart_split(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
void		print_list(t_dict *head);
char		*get_key_env(char *env);
char		*get_value_env(char *env);
t_dict		*new_dict(char *key, char *value);
t_dict		*init_dict(char **env);
void		print_nodes(t_nodes *head);
char		*parsed_str_lst(char *str);
t_nodes		*new_nodes( int i, char **mx);
t_nodes		*init_nodes(char **mx);
int			metacheck(char a, char b, char c);
int			hd_count(char *str);
void		print_list_tenv(t_env *head);
t_env		*init_env_tenv(char **env);
t_env		*new_dict_tenv(char *key, char *value);
void		ft_unset(t_env **head, char *key);
void		multi_unset(t_env **tenv, char **read_line);
void		ft_main_export(t_env **tenv, char **read_line);
void		ft_export(t_env **head, char **rd);
int			hd_count(char *str);
int			append_cnt(char *str);
int			outfile_cnt(char *str);
int			infile_cnt(char *str);
char		**append_init(char *str);
char		**infile_init(char *str);
char		**outfile_init(char *str);
char		**heardock_init(char *str);
char		*find_val_by_key(t_env **tenv, char *key);
void		heredoc_redirect(char *str);
void		infile_redirect(char *file, int fd_s);
char		*gnl(int fd);
int			gnl_cnt(int fd);
void		handler(int sig);
char		*find_val_by_key(t_env **tenv, char *key);
void		print_err(char *str);
void		append_redirect(char *file);
void		outfile_redirect(char *str);
void		single_proc(t_nodes *nds, t_env *tenv, char **env);
void		multi_proc(t_nodes *nds, t_env *tenv, char **env);
void		do_hrd(t_nodes *nds);
void		do_infile(t_nodes *nds, t_env *tenv, char **env);
char		**init_redir(char *str);
char 		**list_to_env(t_env *tenv);
int			find_index(t_env **head, char *key);
char		*ft_itoa(int n);
void 		simple_hrd(char *str);
int			heredoc_count(char *str);
char 		**hd_init(char *str);
void 		ctrl_c(int sig);
char		*ft_strdup(const char *s1);
void		*ft_memcpy(void *dst, const void *src, size_t n);
int			is_infile(char *s);
int			is_outfile(char *s);
int			is_heredoc(char *s);
int			is_append(char *s);
int			is_num(char c);
int			is_alpha(char c);
int			is_space(char c);
int			is_meta(char c);
int			is_al_num_meta_space(char c);
int			is_printable(char c);
char		*removeSpacesFromStr(char *string);
int			heardock_count(char *str);
int			append_count(char *str);
int			infile_count(char *str);
int			outfile_count(char *str);
int			redir_count(char *str);
int	check_single_quotes(char *str);
int	check_double_quotes(char *str);
int	fill_spaces(char **get_line, t_token **token);
int	fill_redirections(char **get_line, t_token **token);
int		fill_quotes_external(char **get_line, t_token **token, int quote);
void	fill_external(char **get_line, t_token **token);
void	fill_expression(char **get_line, t_token **token);
void	set_token(char **get_line, t_token **token);
int		word_len(char *get_line, char ch);
char	*fill_word(char **get_line, char ch, int flag);
char	*epur_str(char *str);
char	*ft_cleanline(char *get_line);
int		get_wordlen_expression(char **heredoc);
char	*execute_expression(char **heredoc);
char	 *find_value_env(t_env	*env, char *key);
int		append_token(t_token **token, int type, char *str);
int		append_env(t_env **env, char *key, char *value);
int		remove_node_from_token(t_token **token, int index);
void	clean_space_from_token(t_token	**token);
void 	print_tok(t_token *tok);
char	*ft_strtrim(char const *s1, char const *set);
char 	**heredoc_fill(t_token *tok);
void remove_hrd(t_token **tok);
char **fill_cmd(t_token *tok);
int is_redirection(int type);

#endif

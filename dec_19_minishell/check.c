#include "./minishell.h"

int	is_infile(char *s)
{
	if(*s == '>' && *(++s) != '>')
		return (1);
	return (0);
}

int	is_outfile(char *s)
{
	if(*s == '<' && *(++s) != '<')
		return (1);
	return (0);
}

int	is_heredoc(char *s)
{
	if(strncmp(s,"<<",2) == 0)
		return (1);
	return (0);
}

int	is_append(char *s)
{
	if(strncmp(s,">>",2) == 0)
		return (1);
	return (0);
}

int	is_num(char c)
{
	if(c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_alpha(char c)
{
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	is_meta(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	is_al_num_meta_space(char c)
{
	if(is_meta(c) || is_alpha(c) || is_num(c) || is_space(c) || c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	is_printable(char c)
{
	if(c >= 32 && c <= 126)
		return (1);
	return (0);
}
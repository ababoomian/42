#include "./minishell.h"

int is_heardock(char a, char b, char c)
{
	if (a == '<' && b == '<' && c != '<')
		if(c == '>' || c == '<')
			return(0);
	return (1);

}
int is_append(char a, char b, char c)
{
	if (a == '>' && b == '>' && c != '>')
		if(c == '>' || c == '<')
			return(0);
	return (1);
}
int is_infile(char a, char b)
{
	if (a == '<' && b != '<')
		return (1);
	return (0);
}
int is_outfile(char a, char b)
{
	if (a == '>' && b != '>')
		return (1);
	return (0);
}

int	metacheck(char a, char b, char c)
{
	if(is_heardock(a,b,c) || is_append(a,b,c) || is_infile(a,b) || is_outfile(a,b))
		return (1);
	return (0);
}
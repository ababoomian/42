#include "./minishell.h"

int	heardock_count(char *str)
{
	int	i;
	int	start;
	char	*s;
	char	*res;
	int	length;

	length = 0;
	res = malloc(ft_strlen(s)+1);
	start = 0;
	i = 0;
	s = strdup(str);
	while(s[i])
	{
		if(is_heredoc(s+i))
		{		
			start = i;
			i+=2;
			while(is_space(s[i]) && s[i])
				i++;
			while(is_printable(s[i]) && !is_space(s[i]) && !is_meta(s[i]))
				i++;
			i--;
			length += ft_strlen(removeSpacesFromStr(ft_substr(s,start, i-start+1))) + 1;
		}
		i++;
	}
	free(s);
	free(res);
	return length;
}

int	append_count(char *str)
{
	int	i;
	int	start;
	char	*s;
	char	*res;
	int	length;

	length = 0;
	res = malloc(ft_strlen(s)+1);
	start = 0;
	i = 0;
	s = strdup(str);
	while(s[i])
	{
		if(is_append(s+i))
		{		
			start = i;
			i+=2;
			while(is_space(s[i]) && s[i])
				i++;
			while(is_printable(s[i]) && !is_space(s[i]) && !is_meta(s[i]))
				i++;
			i--;
			length += ft_strlen(removeSpacesFromStr(ft_substr(s,start, i-start+1))) + 1;
		}
		i++;
	}
	free(s);
	free(res);
	return length;
}

int	infile_count(char *str)
{
	int	i;
	int	start;
	char	*s;
	char	*res;
	int	length;

	length = 0;
	res = malloc(ft_strlen(s)+1);
	start = 0;
	i = 0;
	s = strdup(str);
	while(s[i])
	{
		if(s[i] == '>')
		{		
			i++;
			if(s[i] != '>')
			{
				start = i -1;
				i++;
				while(is_space(s[i]) && s[i])
					i++;
				while(is_printable(s[i]) && !is_space(s[i]) && !is_meta(s[i]))
					i++;
				i--;
				length += ft_strlen(removeSpacesFromStr(ft_substr(s,start, i-start+1))) + 1;
			}	
		}
		i++;
	}
	free(s);
	free(res);
	return length;
}

int	outfile_count(char *str)
{
	int	i;
	int	start;
	// char	*s;
	int		length;

	start = 0;
	i = 0;
	length = 0;
	// s = strdup(str);
	while(str[i])
	{
		if(str[i] == '<')
		{
			i++;
			if(str[i] != '<')
			{
				start = i - 1;
				i++;
				while(is_space(str[i]) && str[i])
					i++;
				i--;
				while(is_printable(str[i]) && !is_space(str[i]) && !is_meta(str[i]))
					i++;
				i--;
			length += ft_strlen(removeSpacesFromStr(ft_substr(str,start, i-start+1))) + 1;
			}
		}
		i++;
	}
	return (length);
}

int	redir_count(char *str)
{
	int	i;
	int	start;
	char	*s;
	char	*res;
	int	length;

	length = 0;
	s = strdup(str);
	res = malloc(ft_strlen(s)+1);
	start = 0;
	i = 0;
	while(s[i])
	{
		if(s[i] == '>')
		{		
			i++;
			if(s[i] != '>')
			{
				start = i -1;
				i++;
				while(is_space(s[i]) && s[i])
					i++;
				while(is_printable(s[i]) && !is_space(s[i]) && !is_meta(s[i]))
					i++;
				i--;
				length += ft_strlen(removeSpacesFromStr(ft_substr(s,start, i-start+1))) + 1;
			}	
		}
		i++;
	}
	free(s);
	free(res);
	return length;
}

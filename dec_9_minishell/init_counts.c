#include "./minishell.h"

int	heardock_count(char *str)
{
	int	i;
	int	start;
	// char	*s;
	int	length;

	length = 0;
	start = 0;
	i = 0;
	// s = strdup(str);
	while(str[i])
	{
		if(is_heredoc(str + i))
		{		
			start = i;
			i+=2;
			while(is_space(str[i]) && str[i])
				i++;
			while(is_printable(str[i]) && !is_space(str[i]) && !is_meta(str[i]))
				i++;
			i--;
			length += ft_strlen(removeSpacesFromStr(ft_substr(str,start, i-start+1))) + 1;
		}
		i++;
	}
	return length;
}

int	append_count(char *str)
{
	int	i;
	int	start;
	// char	*s;
	int		length;

	start = 0;
	length = 0;
	i = 0;
	// s = strdup(str);
	while(str[i])
	{
		if(is_append(str + i))
		{		
			start = i;
			i+=2;
			// dot_check(str+i);
			while(str[i] == ' ' && str[i])
				i++;
			while(is_printable(str[i]) && !is_space(str[i]) && !is_meta(str[i]))
				i++;
			i--;
			length += ft_strlen(removeSpacesFromStr(ft_substr(str,start, i-start+1))) + 1;
		}
		i++;
	}
	return (length);
}

int	infile_count(char *str)
{
	int	i;
	int	start;
	// char	*s;
	int		length;

	start = 0;
	length = 0;
	i = 0;
	// s = strdup(str);
	while(str[i])
	{
		if(str[i] == '>')
		{
			i++;
			if(str[i] != '>')
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
	// char	*s;
	int		length;

	start = 0;
	length = 0;
	i = 0;
	// s = strdup(str);
	while(str[i])
	{
		if(str[i] == '>')
		{
			i++;
			if(str[i] != '>')
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
		else if(str[i] == '<')
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

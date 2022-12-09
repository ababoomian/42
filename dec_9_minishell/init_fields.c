/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fields.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaboom <arbaboom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 03:44:16 by vrsargsy          #+#    #+#             */
/*   Updated: 2022/11/30 18:13:03 by arbaboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./minishell.h"

char *removeSpacesFromStr(char *string)
{
    int non_space_count = 0;
	int	i;
	string[non_space_count++] = string[0];
	
	if(is_meta(string[1]))
	{
		string[non_space_count++] = string[1];
		i = 2;
	}
	else
		i = 1;
	while(is_al_num_meta_space(string[i]))
	{
        if (string[i] != ' ')
        {
            string[non_space_count] = string[i];
            non_space_count++;
        } 
		i++;  
	}
	string[non_space_count] = '\0';
    return string;
}

int is_sep(char c)
{
	if (c == '<' || c == '>' || c == '\0' || !c)
		return (1);
	return (0);
}

char	**heardock_init(char *str)
{
	int	i;
	int	start;
	char	*s;
	char	*res;

	res = malloc(1000);
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
			strcat(res,removeSpacesFromStr(ft_substr(s,start, i-start+1)));
			strcat(res, " ");
		}
		i++;
	}
	free(s);
	return ft_split(res, ' ');
}

// static void	dot_check(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while(!is_sep(str[i]))
// 	{
// 		if(str[i] == '.')
// 		{
// 			perror(" .: Is a directory\n");
// 			exit(1);
// 		}
// 		i++;
// 	}
// }

char	**append_init(char *str)
{
	int	i;
	int	start;
	char	*s;
	char	*res;

	res = malloc(1000);
	start = 0;
	i = 0;
	s = strdup(str);
	while(s[i])
	{
		if(is_append(s+i))
		{		
			start = i;
			i+=2;
			// dot_check(str+i);
			while(s[i] == ' ' && s[i])
				i++;
			while(is_printable(s[i]) && !is_space(s[i]) && !is_meta(s[i]))
				i++;
			i--;
			strcat(res,removeSpacesFromStr(ft_substr(s,start, i-start+1)));
			strcat(res, " ");
		}
		i++;
	}
	free(s);
	return ft_split(res, ' ');
}
 
char	**infile_init(char *str)
{
	int	i;
	int	start;
	char	*s;
	char	*res;

	res = malloc(1000);
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
				start = i - 1;
				i++;
				while(is_space(s[i]) && s[i])
					i++;
				i--;
				while(is_printable(s[i]) && !is_space(s[i]) && !is_meta(s[i]))
					i++;
				i--;
				strcat(res,removeSpacesFromStr(ft_substr(s,start, i-start+1)));
				strcat(res, " ");
			}
		}
		i++;
	}
	free(s);
	return ft_split(res, ' ');
}

char	**outfile_init(char *str)
{
	int	i;
	int	start;
	char	*s;
	char	*res;

	res = malloc(1000);
	start = 0;
	i = 0;
	s = strdup(str);
	while(s[i])
	{
		if(s[i] == '<')
		{
			i++;
			if(s[i] != '<')
			{
				start = i - 1;
				i++;
				while(is_space(s[i]) && s[i])
					i++;
				i--;
				while(is_printable(s[i]) && !is_space(s[i]) && !is_meta(s[i]))
					i++;
				i--;
				strcat(res,removeSpacesFromStr(ft_substr(s,start, i-start+1)));
				strcat(res, " ");
			}
		}
		i++;
	}
	free(s);
	return ft_split(res, ' ');
}

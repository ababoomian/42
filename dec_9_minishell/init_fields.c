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

char	**heardock_init(char *str)
{
	int		i;
	int		j;
	char	*res;

	res = malloc(sizeof(char) * hd_count(str) + 1);
	//printf(UCYN"\n hd :%d\n"RESET,hd_count(str));
	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '<' && str[i + 1] == '<') && str[i + 1] != '\0')
		{
			res[j++] = str[i];
			res[j++] = str[i + 1];
			i += 2;
			while (str[i] && str[i] == 32)
				i++;
			while (str[i] != ' ' && str[i])
			{
				res[j] = str[i];
				i++;
				j++;
			}
		}
		res[j] = ' ';
		j++;
		i++;
	}
	res[j] = '\0';
	return (ft_split(res, ' '));
}

char	**append_init(char *str)
{
	int		i;
	int		j;
	char	*res;

	res = malloc(sizeof(char) * append_cnt(str) + 1);
	//printf(UCYN"\n append : %d\n"RESET,append_cnt(str));
	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '>' && str[i + 1] == '>') && str[i + 1] != '\0')
		{
			res[j++] = str[i];
			res[j++] = str[i + 1];
			i += 2;
			while (str[i] && str[i] == 32)
				i++;
			while (str[i] != ' ' && str[i])
			{
				res[j] = str[i];
				i++;
				j++;
			}
		}
		res[j] = ' ';
		j++;
		i++;
	}
	res[j] = '\0';
	return (ft_split(res, ' '));
}

char	**infile_init(char *str)
{
	int		i;
	int		j;
	char	*res;

	res = malloc(sizeof(char) * infile_cnt(str) + 1);
	//printf(UCYN"\n infile : %d\n"RESET,infile_cnt(str));
	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '>' && str[i + 1] != '>') && str[i + 1] != '\0')
		{
			res[j++] = str[i];
			res[j++] = str[i + 1];
			i += 2;
			while (str[i] && str[i] == 32)
				i++;
			while (str[i] != ' ' && str[i])
			{
				res[j] = str[i];
				i++;
				j++;
			}
		}
		res[j] = ' ';
		j++;
		i++;
	}
	res[j] = '\0';
	return (ft_split(res, ' '));
}

char	**outfile_init(char *str)
{
	int		i;
	int		j;
	char	*res;

	res = malloc(sizeof(char) * outfile_cnt(str) + 1);
	//printf(UCYN"\n outfile : %d\n"RESET,outfile_cnt(str));
	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '<' && str[i + 1] != '<') && str[i + 1] != '\0')
		{
			res[j++] = str[i];
			res[j++] = str[i + 1];
			i += 2;
			while (str[i] && str[i] == 32)
				i++;
			while (str[i] != ' ' && str[i])
			{
				res[j] = str[i];
				i++;
				j++;
			}
		}
		res[j] = ' ';
		j++;
		i++;
	}
	res[j] = '\0';
	return (ft_split(res, ' '));
}

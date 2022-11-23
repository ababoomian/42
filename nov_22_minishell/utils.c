/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaboom <arbaboom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 04:16:47 by vrsargsy          #+#    #+#             */
/*   Updated: 2022/11/23 12:20:55 by arbaboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	dest = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dest || s2 == 0)
		return (0);
	while (s1[i])
		dest[j++] = s1[i++];
	i = 0;
	while (s2[i])
		dest[j++] = s2[i++];
	dest[j] = 0;
	return (dest);
}

char	**init_redir(char *str)
{
	int		i;
	int		j;
	char	*res;

	j = 0;
	i = 0;
	res = malloc(10000);


	while(str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			
			if (str[i + 1] != '<')
			{
				if( str[i + 1] && str[i +  1] == ' ')
				{
					i++;	
					while (str[i] && str[i] == ' ')
						i++;
				}
				j = i;
				while(str[i] &&( str[i] != '<' || str[i] != '>'))
					i++;
				res = ft_strjoin(res,ft_substr(str,j,i - j));
				res = ft_strjoin(res, " ");
			}
			else
			{
				i++;
			}
		}
		i++;
	}
	return(ft_split(res,32));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epur_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrsargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 03:42:20 by vrsargsy          #+#    #+#             */
/*   Updated: 2022/11/18 03:44:10 by vrsargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*epur_str(char *str)
{
	int		i;
	int		flg;
	int		j;
	char	*res;

	j = 0;
	res = malloc(sizeof(char) * 200 + 1);
	if (str && *str)
	{
		i = 0;
		while (str[i] == ' ' || str[i] == '\t')
			i += 1;
		while (str[i])
		{
			if (str[i] == ' ' || str[i] == '\t')
				flg = 1;
			if (!(str[i] == ' ' || str[i] == '\t'))
			{
				if (flg)
				{
					res[j] = 32;
					j++;
				}
				flg = 0;
				res[j] = str[i];
				j++;
			}
			i += 1;
		}
		res[j] = '/';
	}
	return (res);
}

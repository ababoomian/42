/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrsargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 04:15:59 by vrsargsy          #+#    #+#             */
/*   Updated: 2022/11/18 04:16:42 by vrsargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_echo(char **line, t_env *tab)
{
	int	i;

	(void) tab;
	i = 0;
	if (strcmp(line[1], "-n") != 0)
	{
		while (line[++i])
			printf("%s ", line[i]);
		printf("\n");
	}
	else
	{
		i = 1;
		while (line[++i])
			printf("%s ", line[i]);
	}
}

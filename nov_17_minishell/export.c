/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrsargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 04:04:16 by vrsargsy          #+#    #+#             */
/*   Updated: 2022/11/18 04:05:17 by vrsargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./minishell.h"

void	ft_main_export(t_env **tenv, char **read_line)
{
	if (mat_len(read_line) == 1)
		print_list_tenv(*tenv);
	else
	{
		ft_export(tenv, ft_split(read_line[1], '='));
	}
}

void	ft_export(t_env **head, char **rd)
{
	while ((*head)->next)
	{
		if (strcmp((*head)->key, rd[0]) == 0)
		{
			(*head)->value = rd[1];
			(*head)->del = 0;
			return ;
		}
		else
			*head = (*head)->next;
	}
	(*head)->next = new_dict_tenv(rd[0], rd[1]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrsargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 03:28:40 by vrsargsy          #+#    #+#             */
/*   Updated: 2022/11/18 03:29:50 by vrsargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./minishell.h"

int	check_single_quotes(char *str)
{
	int		i;
	int		single_quotes;

	single_quotes = 0;
	i = -1;
	while (str[++i])
		if (str[i] == '\'')
			single_quotes++;
	return (single_quotes % 2);
}

int	check_double_quotes(char *str)
{
	int		i;
	int		double_quotes;

	double_quotes = 0;
	i = -1;
	while (str[++i])
		if (str[i] == '\'')
			double_quotes++;
	return (double_quotes % 2);
}

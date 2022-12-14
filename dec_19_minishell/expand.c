/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrsargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 03:56:03 by vrsargsy          #+#    #+#             */
/*   Updated: 2022/11/18 03:56:31 by vrsargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./minishell.h"

char	*get_expand(char *str, t_env **node)
{
	char	*res;

	res = find_val_by_key(node, ++str);
	return (res);
}

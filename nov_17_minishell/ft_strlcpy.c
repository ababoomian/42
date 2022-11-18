/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrsargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 03:15:39 by vrsargsy          #+#    #+#             */
/*   Updated: 2022/11/18 03:15:42 by vrsargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	id;

	if (!dst || !src)
		return (0);
	id = 0;
	if (dstsize != 0)
	{
		while (src[id] != '\0' && id < (dstsize - 1))
		{
			dst[id] = src[id];
			id++;
		}
		dst[id] = '\0';
	}
	return (ft_strlen(src));
}

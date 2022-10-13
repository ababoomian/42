/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaboom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 11:19:56 by arbaboom          #+#    #+#             */
/*   Updated: 2022/08/27 11:26:17 by arbaboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*get_next_line(int fd)
{
	int		rd;
	int		i;
	char	c;
	char	*buffer;

	i = 0;
	buffer = (char *)malloc(sizeof(char) * 100000);
	rd = read(fd, &c, 1);
	while (rd > 0)
	{
		buffer[i++] = c;
		rd = read(fd, &c, 1);
	}
	if (rd == -1 || (rd == 0 && !buffer[i - 1]))
	{
		free(buffer);
		return (NULL);
	}
	buffer[i] = '\0';
	return (buffer);
}

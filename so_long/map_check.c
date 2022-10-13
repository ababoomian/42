/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaboom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 11:29:36 by arbaboom          #+#    #+#             */
/*   Updated: 2022/08/27 14:01:23 by arbaboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

int	row_count(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	char_count(char **str, char c)
{
	int	p;
	int	i;
	int	j;

	p = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == c)
			{
				p++;
			}
			if (str[i][j] != 'P' && str[i][j] != 'C' && str[i][j] != 'E'
					&& str[i][j] != '1' && str[i][j] != '0')
				return (0);
			j++;
		}
		i++;
	}
	return (p);
}

int	rect_map(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strlen(str[0]) != ft_strlen(str[i])
			|| (row_count(str) < 3 || ft_strlen(str[i]) < 3))
			return (0);
		i++;
	}
	return (1);
}

int	map_frame_val(char **str)
{
	int	i;
	int	len;
	int	j;

	i = -1;
	len = ft_strlen(str[0]);
	while (str[++i])
	{
		j = 0;
		if ((str[i][0] != '1' || str[i][len - 1] != '1'))
			return (0);
		while (str[i][j])
		{
			if (str[0][j] != '1' || str[row_count(str) - 1][j] != '1')
				return (0);
			j++;
		}
	}
	return (1);
}

int	map_val(char **str)
{
	if (*str == NULL || str == NULL)
	{
		ft_putstr("empty file");
		return (0);
	}
	if (!rect_map(str))
	{
		ft_putstr("map is not a rectangle or its smaler than 3x3");
		return (0);
	}
	if (!map_frame_val(str))
	{
		ft_putstr("invalid map frame");
		return (0);
	}
	if ((char_count(str, 'P') != 1) || (char_count(str, 'E') < 1)
		|| (char_count(str, 'C') < 1))
	{
		ft_putstr("invalid element in map");
		return (0);
	}
	return (1);
}

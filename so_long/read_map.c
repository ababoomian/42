/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaboom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 12:17:33 by arbaboom          #+#    #+#             */
/*   Updated: 2022/08/28 18:47:48 by arbaboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	path_check(int ac, char *str)
{
	size_t	i;

	i = ft_strlen(str);
	if (ac != 2)
	{
		ft_putstr("wrong parameter");
		return (0);
	}
	if (str[i - 1] == 'r' && str[i - 2] == 'e'
		&& str[i - 3] == 'b' && str[i - 4] == '.')
		return (1);
	ft_putstr("invalid file path");
	return (0);
}

t_node	*read_map(int ac, char *str)
{
	t_node	*data;
	int		fd;

	data = NULL;
	fd = open(str, O_RDONLY);
	data = (t_node *)malloc(sizeof(t_node) * 1);
	if (fd > 0)
	{
		str = get_next_line(fd);
		data->map = ft_split(str, '\n');
	}
	if (fd < 0)
	{
		ft_putstr("invalid path");
		return (0);
	}
	free(str);
	return (data);
}

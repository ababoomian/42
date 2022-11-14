/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaboom <arbaboom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 11:46:32 by arbaboom          #+#    #+#             */
/*   Updated: 2022/11/13 23:02:32 by arbaboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render(t_node *data)
{
	ft_putnbr(++data -> move);
	write (1, "\n", 1);
	mlx_destroy_window(data -> mlx, data -> win);
	create_map(data, data ->m_w, data ->m_h);
}

int	move_up(t_node *data)
{
	int	i;
	int	j;

	i = -1;
	while (data -> map[++i])
	{
		j = -1;
		while (data -> map[i][++j])
		{
			if (data ->map[i][j] == 'P')
			{
				if (data ->map[i - 1][j] != '1' && data ->map[i - 1][j] != 'E')
				{
					data ->map[i - 1][j] = 'P';
					data -> map[i][j] = '0';
					data -> img_path = "./img/ship_up.xpm";
					render(data);
					return (1);
				}
				if (data -> map[i - 1][j] == 'E')
					ft_exit(data);
			}
		}
	}
	return (0);
}

int	move_down(t_node *data)
{
	int	i;
	int	j;

	i = -1;
	while (data -> map[++i])
	{
		j = -1;
		while (data -> map[i][++j])
		{
			if (data -> map[i][j] == 'P')
			{
				if (data -> map[i + 1][j] != '1' && data ->map[i + 1][j] != 'E')
				{
					data -> map[i + 1][j] = 'P';
					data -> map[i][j] = '0';
					data -> img_path = "./img/ship_down.xpm";
					render(data);
					return (1);
				}
				if (data -> map[i + 1][j] == 'E')
					ft_exit(data);
			}
		}
	}
	return (0);
}

int	move_left(t_node *data)
{
	int	i;
	int	j;

	i = -1;
	while (data -> map[++i])
	{
		j = -1;
		while (data -> map[i][++j])
		{
			if (data -> map[i][j] == 'P')
			{
				if (data -> map[i][j - 1] != '1' && data ->map[i][j - 1] != 'E')
				{
					data -> map[i][j - 1] = 'P';
					data -> map[i][j] = '0';
					data -> img_path = "./img/ship_left.xpm";
					render(data);
					return (1);
				}
				if (data -> map[i][j - 1] == 'E')
					ft_exit(data);
			}
		}
	}
	return (0);
}

int	move_right(t_node *data)
{
	int	i;
	int	j;

	i = -1;
	while (data -> map[++i])
	{
		j = -1;
		while (data -> map[i][++j])
		{
			if (data -> map[i][j] == 'P')
			{
				if (data -> map[i][j + 1] != '1' && data ->map[i][j + 1] != 'E')
				{
					data ->map[i][j + 1] = 'P';
					data -> map[i][j] = '0';
					data -> img_path = "./img/ship_right.xpm";
					render(data);
					return (1);
				}
				if (data ->map[i][j + 1] == 'E')
					ft_exit(data);
			}
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaboom <arbaboom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 10:08:48 by arbaboom          #+#    #+#             */
/*   Updated: 2022/08/28 18:47:10 by arbaboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_exit(t_node *data)
{
	int	i;
	int	j;

	i = -1;
	while (data -> map[++i])
	{
		j = -1;
		while (data -> map[i][++j])
		{
			if (data -> map[i][j] == 'C')
				return ;
		}
	}
	mlx_destroy_window(data -> mlx, data -> win);
	exit(0);
}

int	handler(int keycode, t_node *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars -> mlx, vars -> win);
		exit(0);
	}
	if (keycode == 13 || keycode == 126)
		move_up(vars);
	if (keycode == 0 || keycode == 123)
		move_left(vars);
	if (keycode == 1 || keycode == 125)
		move_down(vars);
	if (keycode == 2 || keycode == 124)
		move_right(vars);
	return (0);
}

void	put_img(t_node *im, char *path, int i, int j)
{
	im -> img = mlx_xpm_file_to_image(im -> mlx, path, &im -> w, &im -> h);
	mlx_put_image_to_window(im -> mlx, im -> win, im -> img, j * 32, i * 32);
}

void	create_map(t_node *data, int w, int h)
{
	int	i;
	int	j;

	i = -1;
	data -> win = mlx_new_window(data -> mlx, w, h, "so_long");
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data ->map[i][j] == '1')
				put_img(data, "./img/wall.xpm", i, j);
			if (data ->map[i][j] == 'P')
				put_img(data, data -> img_path, i, j);
			if (data ->map[i][j] == 'E')
				put_img(data, "./img/exit.xpm", i, j);
			if (data ->map[i][j] == 'C')
				put_img(data, "./img/collectable.xpm", i, j);
		}
	}
	mlx_hook(data -> win, 2, 1L << 0, handler, data);
	mlx_hook(data ->win, 17, 1l << 0, ft_close, data);
	mlx_loop(data -> mlx);
}

int	main(int ac, char **av)
{
	t_node	*data;

	if (ft_strlen(av[1]) && ac == 2 && path_check(ac, av[1]))
	{	
		data = read_map(ac, av[1]);
		if (data)
		{
			if (data ->map)
			{
				if (map_val(data -> map))
				{	
					data -> mlx = mlx_init();
					data -> move = 0;
					data -> img_path = "./img/ship_up.xpm";
					data -> m_w = ft_strlen(data -> map[0]) * 32;
					data -> m_h = row_count(data -> map) * 32;
					create_map(data, data -> m_w, data -> m_h);
				}
			}
		}	
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaboom <arbaboom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 14:07:50 by arbaboom          #+#    #+#             */
/*   Updated: 2022/08/28 18:48:17 by arbaboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>

typedef struct so_long
{
	void	*mlx;
	void	*win;
	void	*img;
	int		w;
	int		h;
	int		move;
	char	*img_path;
	char	**map;
	int		m_w;
	int		m_h;

}				t_node;

size_t		ft_strlen(char *s);
char		*ft_substr(char *s, unsigned int start, size_t len);
char		*get_next_line(int fd);
char		**ft_split(char *s, char c);
int			row_count(char **str);
int			map_val(char **str);
t_node		*read_map(int ac, char *str);
int			handler(int keycode, t_node *vars);
void		create_map(t_node *data, int w, int h);
int			move_up(t_node *data);
int			move_down(t_node *data);
int			move_left(t_node *data);
int			move_right(t_node *data);
void		ft_exit(t_node *data);
int			handler(int keycode, t_node *vars);
void		put_img(t_node *image, char *path, int i, int j);
void		create_map(t_node *data, int w, int h);
void		print_move(t_node *data);
void		ft_putnbr(int n);
void		ft_putchar(char c);
void		ft_putstr(char *s);
int			path_check(int ac, char *str);
int			ft_close(int keycode, t_node *data);
#endif

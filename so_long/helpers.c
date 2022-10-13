/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaboom <arbaboom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 11:26:42 by arbaboom          #+#    #+#             */
/*   Updated: 2022/08/28 18:45:51 by arbaboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	long	number;

	number = n;
	if (number < 0)
	{
		ft_putchar('-');
		number *= -1;
	}
	if (number >= 10)
		ft_putnbr(number / 10);
	ft_putchar('0' + (number % 10));
}

void	ft_putstr(char *s)
{
	unsigned char	*str;

	if (!s)
		return ;
	str = (unsigned char *)s;
	while (*str)
		ft_putchar(*str++);
}

int	ft_close(int keycode, t_node *data)
{
	(void)keycode;
	exit(0);
}

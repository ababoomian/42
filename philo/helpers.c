/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaboom <arbaboom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:46:44 by arbaboom          #+#    #+#             */
/*   Updated: 2022/10/08 17:08:52 by arbaboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi_long(const char *str)
{
	long	a;
	int		b;

	a = 0;
	b = 1;
	if (*str == '0')
		return (0);
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
		{
			b *= -1;
		}
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		a = a * 10 + *str - '0';
		str++;
	}
	return (a * b);
}

int	arg_check(char **av)
{
	int	i;
	int	j;

	i = 1;
			if(ft_atoi_long(av[i]) >= 201)
				return(0);
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	simulate(t_init *main, t_philo *philo)
{
	int			i;
	static int	end = 0;

	i = 0;
	while (i < philo->philo_num)
	{
		if (main ->philo[i].eat_count < 0)
			end++;
		if (end >= main ->philo[0].philo_num && main ->philo[0].sim == 1)
			return (0);
		i++;
	}
	return (1);
}

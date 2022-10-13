/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaboom <arbaboom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:47:14 by arbaboom          #+#    #+#             */
/*   Updated: 2022/10/08 10:22:57 by arbaboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*set_arg(char **av)
{
	int		i;
	t_philo	*data;

	data = NULL;
	i = 0;
	while (av[++i])
		if (ft_atoi_long(av[i]) >= INT_MAX || ft_atoi_long(av[i]) <= 0)
			return (NULL);
	data = (t_philo *)malloc(sizeof(t_philo) * 1);
	data->philo_num = ft_atoi_long(av[1]);
	data->t_to_die = ft_atoi_long(av[2]);
	data->t_to_eat = ft_atoi_long(av[3]);
	data->t_to_sleep = ft_atoi_long(av[4]);
	if (i == 6)
	{
		data->eat_count = ft_atoi_long(av[5]);
		data->sim = 1;
	}
	else
	{
		data->eat_count = -1;
		data->sim = 0;
	}
	return (data);
}

void	fill_philo(t_init *data, t_philo *arg, int i)
{
	data ->philo[i].philo_num = arg ->philo_num;
	data ->philo[i].t_to_eat = arg ->t_to_eat;
	data ->philo[i].t_to_die = arg ->t_to_die;
	data ->philo[i].t_to_sleep = arg ->t_to_sleep;
	data ->philo[i].index = i;
	data ->philo[i].sim = arg->sim;
	data ->philo[i].eat_count = arg ->eat_count;
	pthread_mutex_init(&(data->mut[i]), NULL);
	pthread_mutex_init(data->write, NULL);
	forks(data, i);
}

void	forks(t_init *data, int i)
{
	int	j;

	if (i == data ->philo ->philo_num)
		j = 0;
	else
		j = i + 1;
	data ->philo[i].right = &(data ->mut[i]);
	data ->philo[i].left = &(data ->mut[j]);
	data ->philo[i].write = data ->write;
}

void	print_msg(t_philo *data, char *s, long long start)
{
	printf("%lld : %d : %s\n", get_time() - start, data->index + 1, s);
}

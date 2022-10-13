/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaboom <arbaboom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:25:31 by arbaboom          #+#    #+#             */
/*   Updated: 2022/10/08 11:34:33 by arbaboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *data, long long start)
{
	if (data ->philo_num > 1)
	{
		data ->last_eat = get_time();
		print_msg(data, "philo is eating", start);
		ft_usleep(data ->t_to_eat - 1);
		if (data ->eat_count >= 0)
		{
			data ->eat_count--;
		}
		pthread_mutex_unlock(data ->left);
		pthread_mutex_unlock(data ->right);
	}
}

void	*print(void	*d)
{
	t_philo		*data;
	long long	start;

	data = (t_philo *)d;
	while (*(data ->can_start) == 0)
		;
	start = get_time();
	if (data->index % 2 == 1)
		ft_usleep(data->t_to_eat - 1);
	while (1)
	{
		pthread_mutex_lock(data ->left);
		print_msg(data, "philo has taken a left fork", start);
		if (data->philo_num == 1)
			ft_usleep(data->t_to_die + 2);
		pthread_mutex_lock(data ->right);
		print_msg(data, "philo has taken a right fork", start);
		eat(data, start);
		print_msg(data, "philo is sleeping", start);
		ft_usleep(data ->t_to_sleep - 1);
		print_msg(data, "philo is thinking", start);
	}
	return (0);
}

t_init	*create_thread(t_init *data, t_philo *a)
{
	int			i;
	static int	can_start = 0;
	pthread_t	*tid;
	long long	start;

	i = -1;
	tid = malloc(sizeof(pthread_t) * a ->philo_num);
	data ->philo = malloc(sizeof(t_philo) * a ->philo_num);
	data ->mut = malloc(sizeof(pthread_mutex_t) * a ->philo_num);
	start = get_time();
	if(!tid || !data->philo || !data->mut)
		return(0);
	while (++i < a ->philo_num)
	{
		fill_philo(data, a, i);
		data ->philo[i].can_start = &can_start;
		data ->philo[i].last_eat = start;
		if (pthread_create(tid + i, NULL, &print, &(data ->philo[i])) != 0)
			return (0);
	}
	can_start = 1;
	i = 0;
	while (i < a ->philo_num)
		if (pthread_detach(tid[i++]) != 0)
			return (0);
	free(tid);
	return (data);
}

int	dead_check(t_init *d, t_philo *data, long long start)
{
	int	i;

	i = 0;
	while (i < data ->philo_num)
	{
		if (get_time() - d ->philo[i].last_eat >= d ->philo[i].t_to_die)
		{
			print_msg(&(d ->philo[i]), "philo is died", start);
			return (0);
		}
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_philo		*data;
	t_init		*d;
	long long	start;

	if ((ac < 5 || ac > 6) || !arg_check(av))
		return (0);
	start = get_time();
	d = malloc(sizeof(t_init) * 1);
	data = set_arg(av);
	if (!data)
		return (0);
	d = create_thread(d, data);
	while (*(d ->philo[0].can_start) == 0)
		;
	while (1)
	{
		if (!dead_check(d, data, start) || !simulate(d, data))
			return (0);
	}
	return (0);
}

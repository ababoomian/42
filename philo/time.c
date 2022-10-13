/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaboom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:43:14 by arbaboom          #+#    #+#             */
/*   Updated: 2022/10/04 12:45:54 by arbaboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	long long		i;
	struct timeval	time;

	gettimeofday(&time, NULL);
	i = (time.tv_sec * 1000) + (time.tv_usec * 0.001);
	return (i);
}

void	ft_usleep(long long t)
{
	long long	start;

	start = get_time();
	while (get_time() - start <= t)
		usleep(100);
}

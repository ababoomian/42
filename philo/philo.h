/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaboom <arbaboom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:51:27 by arbaboom          #+#    #+#             */
/*   Updated: 2022/10/06 11:12:47 by arbaboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <string.h>
# include <limits.h>

typedef struct philo
{
	int				philo_num;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				eat_count;
	int				index;
	int				sim;
	int				*can_start;
	long long		last_eat;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*write;
}					t_philo;

typedef struct init
{
	t_philo			*philo;
	pthread_mutex_t	*mut;
	pthread_mutex_t	*write;

}					t_init;

long		ft_atoi_long(const char *str);
long long	get_time(void);
void		ft_usleep(long long t);
t_philo		*set_arg(char **av);
void		fill_philo(t_init *data, t_philo *arg, int i);
void		*print(void *d);
void		forks(t_init *data, int i);
t_init		*create_thread(t_init *data, t_philo *a);
void		forks(t_init *data, int i);
void		print_msg(t_philo *data, char *s, long long start);
int			arg_check(char **av);
int			simulate(t_init *main, t_philo *philo);
#endif

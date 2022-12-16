/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrsargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 04:17:21 by vrsargsy          #+#    #+#             */
/*   Updated: 2022/11/18 04:20:03 by vrsargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_abs(long i)
{
	if (i < 0)
		return (i * -1);
	return (i);
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

long	ft_atoi(const char *str)
{
	size_t				id;
	int					negative;
	unsigned long int	res;

	id = 0;
	negative = 1;
	res = 0;
	while ((str[id] == ' ' || str[id] == '\t')
		|| (str[id] == '\n' || str[id] == '\f')
		|| (str[id] == '\v' || str[id] == '\r'))
		id++;
	if (str[id] == '+' || str[id] == '-')
		if (str[id++] == '-')
			negative *= -1;
	while (ft_isdigit(str[id]))
	{
		res *= 10;
		res += str[id] - '0';
		id++;
	}
	return (res * negative);
}

int	mat_len(char **str)
{
	int	i;

	i = -1;
	while (str[++i] != NULL)
		;
	return (i);
}

int	is_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if ((str[i] < '0' || str[i] > '9') && (str[i] != '-' || str[i] != '+'))
			return (0);
	return (1);
}

int	ft_exit(char **read_line)
{
	if (!read_line[1])
		exit(0);
	if (mat_len(read_line) > 2)
	{
		if (is_digit(read_line[1]))
			printf("to many arguments!!\n");
		else
		{
			printf("exit:\nexit code must be numeric!\n");
			exit(255);
		}
		return (1);
	}
	else
	{
		if (is_digit(read_line[1]) && (ft_atoi(read_line[1]) >= INT_MAX
				|| ft_atoi(read_line[1]) <= INT_MIN))
		{
			printf("exit:\nmust be numeric\n");
			exit(255);
		}
		else if (!is_digit(read_line[1]))
		{
			printf("exit:\nmust be numeric\n");
			exit(255);
		}
		else
		{
			if (ft_atoi(read_line[1]) >= 0)
				exit(ft_atoi(read_line[1]) % 256);
			else
				exit(256 - ft_abs(ft_atoi(read_line[1]) % 256));
		}
	}
}

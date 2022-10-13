/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaboom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:53:37 by arbaboom          #+#    #+#             */
/*   Updated: 2022/09/06 15:56:23 by arbaboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pb(t_node **a, t_node **b)
{	
	if (!b)
		return ;
	push(b, (*a)-> data, 'b');
	pop(a);
}

void	pa(t_node **a, t_node **b)
{
	if (!a)
		return ;
	push(a, (*b)-> data, 'a');
	pop(b);
}

int	smallest(t_node *a, int b)
{
	while (a != NULL)
	{
		if (b > a->data)
			return (0);
		a = a-> next;
	}
	return (1);
}

int	small_index(t_node *a)
{
	int	i;

	i = 0;
	while (a != NULL)
	{
		if (smallest(a, a->data))
			break ;
		a = a->next;
		i++;
	}
	return (i);
}

int	is_sort(t_node *a)
{
	while (a != NULL)
	{
		if (a-> next == NULL)
			return (1);
		if (a->data > a->next ->data)
			return (0);
		a = a->next;
	}
	return (1);
}

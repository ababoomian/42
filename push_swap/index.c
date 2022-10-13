/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaboom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:03:59 by arbaboom          #+#    #+#             */
/*   Updated: 2022/09/06 16:04:32 by arbaboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	indexing(t_node **a, int length)
{
	t_node	*cycle;
	t_node	*min_node;
	int		i;

	min_node = *a;
	cycle = (*a)->next;
	i = 0;
	while (i < length)
	{
		while (cycle)
		{
			if (cycle->index == -1 && min_node->data > cycle->data)
				min_node = cycle;
			cycle = cycle->next;
		}
		min_node->index = i;
		++i;
		cycle = *a;
		min_node = *a;
		while (i < length && min_node->index != -1)
			min_node = min_node->next;
	}
}

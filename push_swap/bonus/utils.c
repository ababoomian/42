/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaboom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 12:13:22 by arbaboom          #+#    #+#             */
/*   Updated: 2022/09/09 12:13:35 by arbaboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./push_swap_bonus.h"

void	pb_bonus(t_node_b **a, t_node_b **b)
{	
	if (!b)
		return ;
	push_b(b, (*a)-> data, '0');
	pop_bonus(a);
}

void	pa_bonus(t_node_b **a, t_node_b **b)
{
	if (!a)
		return ;
	push_b(a, (*b)-> data, '0');
	pop_bonus(b);
}

void	rr_bonus(t_node_b **a, t_node_b **b)
{
	move_to_end_b(a, '0');
	move_to_end_b(b, '0');
}

void	rrr_bonus(t_node_b **a, t_node_b **b)
{
	move_to_front_b(a, '0');
	move_to_front_b(b, '0');
}

void	ss_bonus(t_node_b **a, t_node_b **b)
{
	ft_swap_b(a, '0');
	ft_swap_b(b, '0');
}

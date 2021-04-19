/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 01:37:53 by dwanetta          #+#    #+#             */
/*   Updated: 2021/04/19 01:40:07 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check(double n1, double n2)
{
	if (n1 > n2)
		return (0);
	else
		return (1);
}

void	sort_help(t_sprite **pr, t_sprite **q, t_sprite **p, t_sprite **out)
{
	if (*pr == NULL)
	{
		(*q)->next = *out;
		*out = *q;
	}
	else
	{
		(*q)->next = *p;
		(*pr)->next = *q;
	}
}

t_sprite	*sort_list(t_sprite *head)
{
	t_sprite	*q;
	t_sprite	*out;
	t_sprite	*p;
	t_sprite	*pr;

	out = NULL;
	while (head != NULL)
	{
		q = head;
		head = head->next;
		p = out;
		pr = NULL;
		while (p != NULL && check(q->dist, p->dist) > 0)
		{
			pr = p;
			p = p->next;
		}
		sort_help(&pr, &q, &p, &out);
	}
	return (out);
}

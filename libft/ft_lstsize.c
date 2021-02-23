/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 19:36:24 by dwanetta          #+#    #+#             */
/*   Updated: 2020/11/04 19:51:53 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	if (lst)
	{
		while (lst->next != NULL)
		{
			lst = lst->next;
			i++;
		}
		return (i + 1);
	}
	return (i);
}

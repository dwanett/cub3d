/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 19:22:36 by dwanetta          #+#    #+#             */
/*   Updated: 2020/11/04 19:27:53 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = (t_list*)malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	(*list).content = content;
	(*list).next = NULL;
	return (list);
}

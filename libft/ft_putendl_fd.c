/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:31:00 by dwanetta          #+#    #+#             */
/*   Updated: 2020/11/03 21:46:49 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;
	int size;

	i = 0;
	if (s != NULL)
	{
		size = ft_strlen(s);
		write(fd, s, size);
		write(fd, "\n", 1);
	}
}

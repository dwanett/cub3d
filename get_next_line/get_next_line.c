/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 15:31:58 by dwanetta          #+#    #+#             */
/*   Updated: 2021/01/08 14:59:40 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strleng(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

int		ft_read_line(int fd, char *buf)
{
	int	size;
	int	check_n;

	check_n = 0;
	if (fd < 0)
		return (-1);
	size = read(fd, buf, BUFFER_SIZE);
	buf[size] = '\0';
	while (buf[check_n] != '\n' && buf[check_n] != '\0')
		check_n++;
	if (check_n < size)
		return (1);
	if (size == 0 || size < BUFFER_SIZE)
		return (0);
	if (size < 0)
		return (-1);
	return (1);
}

int		ft_save_buf(t_lists **save, char *buf, int fd, int return_value)
{
	int		check_n;
	int		size;
	t_lists	*tmp;

	check_n = 0;
	tmp = *save;
	while (*save != NULL && (*save)->fd != fd)
		*save = (*save)->next;
	if (*save == NULL)
	{
		while (buf[check_n] != '\n')
			check_n++;
		size = ft_strleng(buf + check_n + 1);
		if (((*save) = (t_lists *)malloc(sizeof(t_lists))) == NULL)
			return (-1);
		if (((*save)->str = (char *)malloc(sizeof(char) * size + 1)) == NULL)
			return (-1);
		ft_memcpyg((*save)->str, buf + check_n + 1, size);
		(*save)->fd = fd;
		(*save)->return_vla = return_value;
		(*save)->next = tmp;
		return (1);
	}
	return (return_value);
}

int		ft_check(t_lists **save, int fd)
{
	t_lists	*tmp;

	tmp = *save;
	while (*save != NULL && (*save)->fd != fd)
		*save = (*save)->next;
	if (*save != NULL && (*save)->fd == fd)
	{
		*save = tmp;
		return (0);
	}
	*save = tmp;
	return (1);
}

int		get_next_line(int fd, char **line)
{
	char			buf[BUFFER_SIZE + 1];
	int				return_value;
	int				check_n;
	static t_lists	*save;

	check_n = 0;
	if (BUFFER_SIZE <= 0 || read(fd, buf, 0) < 0 || !line)
		return (-1);
	if (!(*line = NULL) && save != NULL && (ft_check(&save, fd) == 0))
		return_value = ft_read_save(line, buf, &save, fd);
	else
	{
		while ((check_n == ft_strleng(buf) && return_value > 0) || *line == NULL)
		{
			check_n = 0;
			return_value = ft_read_line(fd, buf);
			while (buf[check_n] != '\n' && buf[check_n] != '\0')
				check_n++;
			if ((*line = ft_strjoing(*line, buf, check_n)) == NULL)
				return (-1);
		}
		if (return_value == 1)
			return_value = ft_save_buf(&save, buf, fd, return_value);
	}
	return (return_value);
}

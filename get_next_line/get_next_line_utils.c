/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 15:32:01 by dwanetta          #+#    #+#             */
/*   Updated: 2021/01/05 19:42:54 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoing(char *s1, char *s2, int check_n)
{
	char	*str;
	int		i;
	int		j;
	int		k;
	int		size;

	i = 0;
	j = 0;
	k = 0;
	size = ft_strleng(s2);
	if (check_n != size && size != 0)
		size = check_n;
	if (!(str = (char *)malloc(sizeof(char) * (size + ft_strleng(s1) + 1))))
		return (NULL);
	while ((s2[j] != '\0' && s2[j] != '\n') || (s1 != NULL && s1[k] != '\0'))
	{
		if (s1 != NULL && s1[k] != '\0')
			str[i] = s1[k++];
		else
			str[i] = s2[j++];
		i++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

void	ft_memcpyg(void *dst, void *src, int n)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	tmp = (char *)dst;
	tmp2 = (char *)src;
	if (n < 0)
		n = 0;
	if (tmp != NULL || tmp2 != NULL)
		while (i != n)
		{
			tmp[i] = tmp2[i];
			i++;
		}
	tmp[i] = '\0';
}

int		ft_add_in_save(char *buf, t_lists **save, int fd, int check_n)
{
	int		return_value;
	int		size_save_str;
	char	*tmp;

	size_save_str = ft_strleng((*save)->str);
	return_value = 1;
	while (check_n == size_save_str && return_value != 0)
	{
		check_n = 0;
		return_value = ft_read_line(fd, buf);
		tmp = (*save)->str;
		if (((*save)->str = (char*)malloc(sizeof(char) *
		(size_save_str + ft_strleng(buf) + 1))) == NULL)
			return (-1);
		ft_memcpyg((*save)->str, tmp, size_save_str);
		ft_memcpyg((*save)->str + size_save_str, buf, ft_strleng(buf));
		free(tmp);
		while ((*save)->str[check_n] != '\n' && (*save)->str[check_n] != '\0')
			check_n++;
		size_save_str = ft_strleng((*save)->str);
	}
	(*save)->return_vla = return_value;
	return (check_n);
}

void	ft_free_save(t_lists **root, t_lists **del)
{
	t_lists	*tmp_save;

	tmp_save = *root;
	while (tmp_save != NULL && tmp_save->next != *del && tmp_save != *del)
		tmp_save = tmp_save->next;
	if (tmp_save == *del)
		*root = (*root)->next;
	else if ((*del)->next == NULL)
		tmp_save->next = NULL;
	else
		tmp_save->next = (*del)->next;
	free((*del)->str);
	(*del)->next = NULL;
	free(*del);
}

int		ft_read_save(char **line, char *buf, t_lists **save, int fd)
{
	t_lists	*tmp_save;
	int		n;
	char	*tmp;

	n = 0;
	tmp_save = *save;
	while (*save != NULL && (*save)->fd != fd)
		*save = (*save)->next;
	if (*save != NULL)
	{
		while ((*save)->str[n] != '\n' && (*save)->str[n] != '\0')
			n++;
		if (n == ft_strleng((*save)->str))
			n = ft_add_in_save(buf, save, fd, n);
		*line = ft_strjoing(*line, (*save)->str, n);
		tmp = (*save)->str;
		if (!((*save)->str = malloc(sizeof(char) * ft_strleng(n + tmp) + 1)))
			return (-1);
		ft_memcpyg((*save)->str, tmp + n + 1, ft_strleng(n + tmp));
		free(tmp);
	}
	if ((fd = (*save)->return_vla) == 0)
		ft_free_save(&tmp_save, save);
	*save = tmp_save;
	return (fd);
}

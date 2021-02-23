/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 15:31:56 by dwanetta          #+#    #+#             */
/*   Updated: 2021/02/19 17:54:57 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 32

# include <unistd.h>
# include <stdlib.h>

typedef struct		s_lists
{
	char			*str;
	int				return_vla;
	int				fd;
	struct s_lists	*next;
}					t_lists;

int					ft_read_save(char **line, char *buf, t_lists **save, int fd);
int					ft_strleng(char *str);
int					ft_read_line(int fd, char *buf);
void				ft_memcpyg(void *dst, void *src, int n);
char				*ft_strjoing(char *s1, char *s2, int check_n);
int					get_next_line(int fd, char **line);

#endif

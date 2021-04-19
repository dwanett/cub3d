/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_save_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:34:22 by dwanetta          #+#    #+#             */
/*   Updated: 2021/03/09 15:54:17 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_last_str_map(char **tmp_map)
{
	int	i;

	i = ft_strlen(*tmp_map);
	while (tmp_map[0][i] != '1')
		i--;
	while (tmp_map[0][i] != '\n')
	{
		if (tmp_map[0][i] != ' ' && tmp_map[0][i] != '1')
			return (0);
		i--;
	}
	if (i == 0)
		return (0);
	return (1);
}

void	ft_save_map(char *line, char **tmp_map, int *return_gnl)
{
	char	*tmp;

	if (line[0] == '\0' && *return_gnl == 1
		&& *tmp_map != NULL && check_last_str_map(tmp_map) != 1)
	{
		ft_putstr_fd("Error\nInvalid map\n", 1);
		exit(-1);
	}
	if (line[0] != '\0')
	{
		if (*tmp_map == NULL)
		{
			*tmp_map = line;
			*tmp_map = ft_strjoin(*tmp_map, "\n");
		}
		else
		{
			tmp = *tmp_map;
			*tmp_map = ft_strjoin(*tmp_map, line);
			free(tmp);
			tmp = *tmp_map;
			*tmp_map = ft_strjoin(*tmp_map, "\n");
			free(tmp);
		}
	}
}

int	help_check_map(char **map, int *flag_player, int *i, int *j)
{
	if ((*i == 0 || map[*i + 1] == NULL)
		&& map[*i][*j] != '1' && map[*i][*j] != ' ')
		return (-1);
	if (*i > 0 && map[*i + 1] != NULL && map[*i][*j] != '1'
		&& map[*i][*j] != ' ' && (map[*i + 1][*j] == ' '
		|| map[*i - 1][*j] == ' ' || map[*i][*j + 1] == ' '
		|| map[*i][*j - 1] == ' ' || map[*i - 1][*j - 1] == ' '
		|| map[*i + 1][*j + 1] == ' ' || map[*i - 1][*j + 1] == ' '
		|| map[*i + 1][*j - 1] == ' '))
		return (-1);
	if (*i > 0 && map[*i + 1] != NULL && map[*i][*j] != ' '
		&& map[*i][*j] != '1' && (map[*i + 1][*j] == '\0'
		|| map[*i - 1][*j] == '\0' || map[*i][*j + 1] == '\0'
		|| map[*i][*j - 1] == '\0' || map[*i - 1][*j - 1] == '\0'
		|| map[*i + 1][*j + 1] == '\0' || map[*i - 1][*j + 1] == '\0'
		|| map[*i + 1][*j - 1] == '\0'))
		return (-1);
	if ((map[*i][*j] == 'N' || map[*i][*j] == 'S' || map[*i][*j] == 'W'
		|| map[*i][*j] == 'E') && *flag_player == 0)
		*flag_player = 1;
	if (map[*i][*j] != ' ' && map[*i][*j] != '0' && map[*i][*j] != '1'
		&& map[*i][*j] != '2' && map[*i][*j] != 'N' && map[*i][*j] != 'S'
		&& map[*i][*j] != 'W' && map[*i][*j] != 'E')
		return (-1);
	return (0);
}

int	check_map(char **map)
{
	int	i;
	int	j;
	int	flag_player;

	i = 0;
	flag_player = 0;
	if (map == NULL)
		return (-1);
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (help_check_map(map, &flag_player, &i, &j) == -1)
				return (-1);
			j++;
		}
		if (map[i][j - 1] != '1')
			return (-1);
		i++;
	}
	if (flag_player == 0)
		return (-1);
	return (0);
}

int	ft_check_init_file(t_file *file)
{
	if (file->R_x < 1 || file->R_y < 1)
	{
		ft_putstr_fd("Error\nInvalid resolution\n", 1);
		return (-1);
	}
	if (file->F[0] < 0 || file->F[1] < 0 || file->F[2] < 0
		|| file->F[0] > 255 || file->F[1] > 255 || file->F[2] > 255)
	{
		ft_putstr_fd("Error\nInvalid floor color "
			"([0-255], [0-255], [0-255])\n", 1);
		return (-1);
	}
	if (file->C[0] < 0 || file->C[1] < 0 || file->C[2] < 0
		|| file->C[0] > 255 || file->C[1] > 255 || file->C[2] > 255)
	{
		ft_putstr_fd("Error\nInvalid ceiling color "
			"([0-255], [0-255], [0-255])\n", 1);
		return (-1);
	}
	if (check_map(file->map) == -1)
	{
		ft_putstr_fd("Error\nInvalid map\n", 1);
		return (-1);
	}
	return (0);
}

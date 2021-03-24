/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:29:56 by dwanetta          #+#    #+#             */
/*   Updated: 2021/03/24 12:20:50 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_init_file_int(char *line, int *i)
{
	int	k;

	k = 0;
	while (line[*i] != '\0')
	{
		while (ft_isdigit(line[*i]) == 0)
			*i += 1;
		k = *i;
		while (ft_isdigit(line[*i]) == 1)
			*i += 1;
		return (ft_atoi(line + k));
	}
	return (0);
}

void	ft_init_file_char(char *line, t_file *file,
					char **tmp_map, int *return_gnl)
{
	if (line[0] == 'N' && line[1] == 'O' && *tmp_map == NULL)
		file->NO_texture = ft_strtrim(line + 2, " ");
	else if (line[0] == 'S' && line[1] == 'O' && *tmp_map == NULL)
		file->SO_texture = ft_strtrim(line + 2, " ");
	else if (line[0] == 'W' && line[1] == 'E' && *tmp_map == NULL)
		file->WE_texture = ft_strtrim(line + 2, " ");
	else if (line[0] == 'E' && line[1] == 'A' && *tmp_map == NULL)
		file->EA_texture = ft_strtrim(line + 2, " ");
	else if (line[0] == 'S' && line[1] != 'O' && *tmp_map == NULL)
		file->S_texture = ft_strtrim(line + 1, " ");
	else if (file->R_x != 0 && file->R_y != 0 && file->NO_texture != NULL
				&& file->SO_texture != NULL && file->WE_texture != NULL
				&& file->EA_texture != NULL && file->S_texture != NULL)
		ft_save_map(line, tmp_map, return_gnl);
	else if (line[0] != '\0')
	{
		ft_putstr_fd("Error\nInvalid file\n", 1);
		exit(-1);
	}
}

void	ft_init_file(char *line, t_file *file, char **tmp_map, int *return_gnl)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (line[0] == 'R' && *tmp_map == NULL)
	{
		file->R_x = ft_init_file_int(line, &i);
		file->R_y = ft_init_file_int(line, &i);
	}
	else if (line[0] == 'F' && *tmp_map == NULL)
		while (j != 3)
			file->F[j++] = ft_init_file_int(line, &i);
	else if (line[0] == 'C' && *tmp_map == NULL)
		while (j != 3)
			file->C[j++] = ft_init_file_int(line, &i);
	else
		ft_init_file_char(line, file, tmp_map, return_gnl);
}

int		ft_pars(int fd, t_file *file)
{
	char	*line;
	char	*tmp_map;
	int		i;

	i = 1;
	file->R_x = 0;
	file->R_y = 0;
	file->NO_texture = NULL;
	file->SO_texture = NULL;
	file->WE_texture = NULL;
	file->EA_texture = NULL;
	file->S_texture = NULL;
	tmp_map = NULL;
	while (i > 0)
	{
		i = get_next_line(fd, &line);
		if (i == -1)
			return (-1);
		ft_init_file(line, file, &tmp_map, &i);
		free(line);
	}
	file->map = ft_split(tmp_map, '\n');
	free(tmp_map);
	return (0);
}

int		ft_open_file(int argc, char *argv[], t_file *file)
{
	int	fd;
	int	size_argv;
	int	check_dot;
	int i;

	check_dot = 0;
	i = 0;
	if (argc <= 1 || argc >= 4)
	{
		ft_putstr_fd("Error\nNumber of arguments\n", 1);
		return (-1);
	}
	while (argv[1][i] != '\0')
	{
		if (argv[1][i] == '.')
			check_dot++;
		i++;
	}
	size_argv = ft_strlen(argv[1]) - 1;
	if (argv[1][size_argv - 3] != '.' || argv[1][size_argv - 2] != 'c'
	|| argv[1][size_argv - 1] != 'u' || argv[1][size_argv] != 'b' || check_dot > 1)
	{
		ft_putstr_fd("Error\nInvalid file extension\n", 1);
		return (-1);
	}
	fd = open(argv[1], O_RDONLY);
	return (ft_pars(fd, file));
}

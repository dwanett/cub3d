/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:33:24 by dwanetta          #+#    #+#             */
/*   Updated: 2021/03/02 16:23:58 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int ft_init_file_int(char *line, int *i)
{
	int k;

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

void ft_init_file_char(char *line, t_file *file, char **tmp_map)
{
	char *tmp;

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
	else if (line[0] != '\0')
	{
		ft_putstr_fd("Error\nInvalid file\n", 1);
		exit(-1);
	}
}

void ft_init_file(char *line, t_file *file, char **tmp_map)
{
	int i;
	int j;

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
		ft_init_file_char(line, file, tmp_map);
}

int ft_pars(int fd, t_file *file)
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
		ft_init_file(line, file, &tmp_map);
		free(line);
	}
	file->map = ft_split(tmp_map, '\n');
	free(tmp_map);
	return (0);
}

int ft_open_file(int argc, char *argv[], t_file *file)
{
	int fd;
	int size_argv;

	if (argc <= 1 || argc >= 4)
	{
		ft_putstr_fd("Error\nNumber of arguments\n", 1);
		return (-1);
	}
	size_argv = ft_strlen(argv[1]) - 1;
	if (argv[1][size_argv - 3] != '.' || argv[1][size_argv - 2] != 'c'
	|| argv[1][size_argv - 1] != 'u' || argv[1][size_argv] != 'b')
	{
		ft_putstr_fd("Error\nInvalid file extension\n", 1);
		return (-1);
	}
	fd = open(argv[1], O_RDONLY);
	return (ft_pars(fd, file));
}

int check_map(char **map)
{
	int i;
	int j;

	i = 0;
	if (map == NULL)
		return (-1);
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			//printf("map[%d][%d] = %c\n", i, j, map[i][j]);
			if ((i == 0 || map[i + 1] == NULL) && map[i][j] != '1' && map[i][j] != ' ')
				return (-1);
			j++;
		}
		//printf("map[%d] = %s\n", i, map[i]);
		i++;
	}
	return (0);
}

int ft_check_init_file(t_file *file)
{
	int return_value;

	return_value  = 0;
	if (file->R_x < 1 || file->R_y < 1)
	{
		ft_putstr_fd("Error\nInvalid resolution\n", 1);
		return_value = -1;
	}
	if (file->F[0] < 0 || file->F[1] < 0 || file->F[2] < 0 ||
	 file->F[0] > 255 || file->F[1] > 255 || file->F[2] > 255)
	{
		ft_putstr_fd("Error\nInvalid floor color ([0-255], [0-255], [0-255])\n", 1);
		return_value = -1;
	}
	if (file->C[0] < 0 || file->C[1] < 0 || file->C[2] < 0 ||
		file->C[0] > 255 || file->C[1] > 255 || file->C[2] > 255)
	{
		ft_putstr_fd("Error\nInvalid ceiling color ([0-255], [0-255], [0-255])\n", 1);
		return_value = -1;
	}
	if (check_map(file->map) == -1)
	{
		ft_putstr_fd("Error\nInvalid map\n", 1);
		return_value = -1;
	}
	return(return_value);
}

void full_free_file(t_file *file)
{
	int i;

	i = 0;
	free(file->NO_texture);
	free(file->SO_texture);
	free(file->WE_texture);
	free(file->EA_texture);
	free(file->S_texture);
	while (file->map[i] != NULL)
		free(file->map[i++]);
	free(file->map);
}

int main(int argc, char *argv[])
{
	t_file file;
	int i;

	i = 0;
	if (ft_open_file(argc, argv, &file) == -1)
		exit(-1);
	if (ft_check_init_file(&file) == -1)
		exit(-1);
	printf("x = %d\n", file.R_x);
	printf("y = %d\n", file.R_y);
	printf("NO_texture = %s\n", file.NO_texture);
	printf("SO_texture = %s\n", file.SO_texture);
	printf("WE_texture = %s\n", file.WE_texture);
	printf("EA_texture = %s\n", file.EA_texture);
	printf("S_texture  = %s\n", file.S_texture);
	printf("F = %d,%d,%d\n", file.F[0], file.F[1], file.F[2]);
	printf("C = %d,%d,%d\n", file.C[0], file.C[1], file.C[2]);
	while (file.map[i] != NULL)
	{
		printf("map[%2d] = %s\n", i ,file.map[i]);
		i++;
	}
	full_free_file(&file);
}
	/*
void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}*/
	/*
	while (x != 100)
	{
		y = (149*x-50) / 99;
		mlx_pixel_put(mlx, mlx_win, x, y, 0x00ff0000);
		x++;
	}
012NSEW
*/
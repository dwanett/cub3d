/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:33:24 by dwanetta          #+#    #+#             */
/*   Updated: 2021/02/25 23:30:06 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void ft_init_file(char *line, t_file *file)
{
	int i;

	i = 0;
	if (line[0] == 'R')
	{
		while (ft_isdigit(line[i]) == 0)
			i++;
		file->R_x = ft_atoi(line + i);
		while (ft_isdigit(line[i]) == 1)
			i++;
		file->R_y = ft_atoi(line + i);
	}
	else if (line[0] == 'F')
	{
		while (ft_isdigit(line[i]) == 0)
			i++;
		file->F[0] = ft_atoi(line + i);
		while (ft_isdigit(line[i]) == 1)
			i++;
		i++;
		file->F[1] = ft_atoi(line + i);
		while (ft_isdigit(line[i]) == 1)
			i++;
		i++;
		file->F[2] = ft_atoi(line + i);
	}
	else if (line[0] == 'C')
	{
		while (ft_isdigit(line[i]) == 0)
			i++;
		file->C[0] = ft_atoi(line + i);
		while (ft_isdigit(line[i]) == 1)
			i++;
		i++;
		file->C[1] = ft_atoi(line + i);
		while (ft_isdigit(line[i]) == 1)
			i++;
		i++;
		file->C[2] = ft_atoi(line + i);
	}
	else if (line[0] == 'N' && line[1] == 'O')
		file->NO_texture = ft_strtrim(line + 2, " ");
	else if (line[0] == 'S' && line[1] == 'O')
		file->SO_texture = ft_strtrim(line + 2, " ");
	else if (line[0] == 'W' && line[1] == 'E')
		file->WE_texture = ft_strtrim(line + 2, " ");
	else if (line[0] == 'E' && line[1] == 'A')
		file->EA_texture = ft_strtrim(line + 2, " ");
	else if (line[0] == 'S' && line[1] != 'O')
		file->S_texture = ft_strtrim(line + 2, " ");
}

int	ft_pars(int fd)
{
	t_file	file;
	char	*line;
	int		i;

	i = 1;
	file.R_x = 0;
	file.R_y = 0;
	file.NO_texture = NULL;
	file.SO_texture = NULL;
	file.WE_texture = NULL;
	file.EA_texture = NULL;
	file.S_texture = NULL;
	file.map = NULL;
	while (i > 0)
	{
		i = get_next_line(fd, &line);
		if (i == -1)
			break ;
		ft_init_file(line, &file);
	}
	printf("x = %d\n", file.R_x);
	printf("y = %d\n", file.R_y);
	printf("NO_texture = %s\n", file.NO_texture);
	printf("SO_texture = %s\n", file.SO_texture);
	printf("WE_texture = %s\n", file.WE_texture);
	printf("EA_texture = %s\n", file.EA_texture);
	printf("S_texture = %s\n", file.S_texture);
	printf("F = %d,%d,%d\n", file.F[0], file.F[1], file.F[2]);
	printf("C = %d,%d,%d\n", file.C[0], file.C[1], file.C[2]);
}

int ft_open_file(int argc, char *argv[])
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
	return (ft_pars(fd));
}

int main(int argc, char *argv[])
{

	if (ft_open_file(argc, argv) == -1)
		exit(-1);
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
*/
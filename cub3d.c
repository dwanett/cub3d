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

	}
}

int	ft_pars(fd)
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
	file.C[0] = 0;
	file.C[0] = 0;
	file.map = NULL;
	while (i > 0)
	{
		i = get_next_line(fd, &line);
		if (i == -1)
			break ;
		ft_init_file(line, &file);
	}
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
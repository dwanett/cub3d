/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:33:24 by dwanetta          #+#    #+#             */
/*   Updated: 2021/03/16 20:32:55 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	full_free_file(t_file *file)
{
	int	i;

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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void print_kodred(t_all *all, int size, int color, int x, int y)
{
	int tmp_y;
	int tmp_x;

	tmp_y = y;
	tmp_x = x;
	while (x < (tmp_x + size))
	{
		y = tmp_y;
		while (y < (tmp_y + size))
		{
			my_mlx_pixel_put(&all->data, x, y, color);
			y += 1;
		}
		x += 1;
	}
}

/*void print_line(t_all *all, int x1, int y1, int x2, int y2)
{
	int dX;
	int dY;
	int signX;
	int signY;
	int error;
	int error2;

	dX = abs(x2 - x1);
	dY = abs(y2 - y1);
	signX = x1 < x2 ? 1 : -1;
	signY = y1 < y2 ? 1 : -1;
	error = dX - dY;
	my_mlx_pixel_put(&all->data, x2, y2, 0x00FF0000);
	while(x1 != x2 || y1 != y2)
	{
		my_mlx_pixel_put(&all->data, x1, y1, 0x00FF0000);
		error2 = error * 2;
		if(error2 > -dY)
		{
			error -= dY;
			x1 += signX;
		}
		if(error2 < dX)
		{
			error += dX;
			y1 += signY;
		}
	}

}*/

void create_map(char **map, t_all *all)
{
	int color;

	color = 0x00000000;
	while (map[all->map_mass.x] != NULL)
	{
		while (map[all->map_mass.x][all->map_mass.y] != '\0')
		{
			if (map[all->map_mass.x][all->map_mass.y] == ' ')
				color = 0x00000000;
			if (map[all->map_mass.x][all->map_mass.y] == '1')
				color = 0x000FF000;
			if (map[all->map_mass.x][all->map_mass.y] == '0')
				color = 0x000FFFF0;
			if (map[all->map_mass.x][all->map_mass.y] == 'N' ||
			map[all->map_mass.x][all->map_mass.y] == 'S' ||
			map[all->map_mass.x][all->map_mass.y] == 'E' ||
			map[all->map_mass.x][all->map_mass.y] == 'W' &&
			all->player.x == 0)
			{
				if (map[all->map_mass.x][all->map_mass.y] == 'S')
					all->angle.alpha = 90;
				if (map[all->map_mass.x][all->map_mass.y] == 'W')
					all->angle.alpha = 180;
				if (map[all->map_mass.x][all->map_mass.y] == 'N')
					all->angle.alpha = 270;
				if (map[all->map_mass.x][all->map_mass.y] == 'E')
					all->angle.alpha = 0;
				all->player.x = all->map_mass.y * SIZE_CHUNK + all->map_mass.y;
				all->player.y = all->map_mass.x * SIZE_CHUNK + all->map_mass.x;
				map[all->map_mass.x][all->map_mass.y] = '0';
				color = 0x000FFFF0;
			}
			print_kodred(all, SIZE_CHUNK, color, all->pix_for_map.x, all->pix_for_map.y);
			all->pix_for_map.x += SIZE_CHUNK;
			all->pix_for_map.y += SIZE_CHUNK;
			all->pix_for_map.y -= SIZE_CHUNK;
			all->map_mass.y++;
			all->pix_for_map.x++; //black line
		}
		all->map_mass.y = 0;
		all->pix_for_map.x = 0;
		all->pix_for_map.y++; //black line
		all->pix_for_map.y += SIZE_CHUNK;
		all->map_mass.x++;
	}
}

void create_player(t_all *all)
{
	int	tmp_y;
	int	tmp_x;

	tmp_y = (int)all->player.y;
	tmp_x = (int)all->player.x;
	print_kodred(all, SIZE_PLAYER, 0x00FF0000, tmp_x, tmp_y);
}

void print_line(t_all *all, double x1, double y1, double x2, double y2)
{
	int deltaX;
	int deltaY;
	int length;
	double dX;
	double dY;

	deltaX = abs(round(x1) - round(x2));
	deltaY = abs(round(y1) - round(y2));
	length = MAX(deltaX, deltaY);
	if (length == 0)
	{
		my_mlx_pixel_put(&all->data, round(x1),  round(y1), 0x00FF0000);
		return;
	}
	dX = (x2 - x1) / length;
	dY = (y2 - y1) / length;
	length++;
	while (length--)
	{
		x1 += dX;
		y1 += dY;
		my_mlx_pixel_put(&all->data, round(x1),  round(y1), 0x00FF0000);
	}
}

/*void reycast(t_all *all)
{
	double	ugl;
	double	x;
	double	y;
	int		col;
	int		i;

	ugl = all->angle.alpha * PI / 180;
	col = 1;
	i = 0;
	while (ugl <= (PI + all->angle.alpha * PI / 180) || i < col)
	{
		x = (all->player.x + (SIZE_PLAYER / 2.0)) + (50 * cos(ugl));
		y = (all->player.y + (SIZE_PLAYER / 2.0)) + (50 * sin(ugl));
		print_line(all, (int)all->player.x + (SIZE_PLAYER / 2.0), (int)all->player.y + (SIZE_PLAYER / 2.0), (int)x, (int)y);
		ugl += ((PI * 2) - PI) / (col - 1);
		i++;
	}
	//printf("%d\n", i);
}*/

void reycast(t_all *all)
{
	double	ugl;
	double	x;
	double	y;
	int		col;
	int		i;

	ugl = all->angle.alpha * PI / 180;
	col = 1;
	i = 0;
	while (ugl <= (PI + all->angle.alpha * PI / 180) || i < col)
	{
		x = (all->player.x + (SIZE_PLAYER / 2.0)) + (50 * cos(ugl));
		y = (all->player.y + (SIZE_PLAYER / 2.0)) + (50 * sin(ugl));
		print_line(all, (int)all->player.x + (SIZE_PLAYER / 2.0), (int)all->player.y + (SIZE_PLAYER / 2.0), (int)x, (int)y);
		ugl += ((PI * 2) - PI) / (col - 1);
		i++;
	}
	//printf("%d\n", i);
}

void move(t_all *all)
{
	if (all->key.keycode == W)
	{
		all->player.x += SPEED * cos((all->angle.alpha * PI / 180));
		all->player.y += SPEED * sin((all->angle.alpha * PI / 180));
	}
	if (all->key.keycode == S)
	{
		all->player.x -= SPEED * cos((all->angle.alpha * PI / 180));
		all->player.y -= SPEED * sin((all->angle.alpha * PI / 180));
	}
	if (all->key.keycode == A)
	{
		all->player.x -= SPEED * cos((all->angle.alpha * PI / 180) + PI / 2);
		all->player.y -= SPEED * sin((all->angle.alpha * PI / 180) + PI / 2);
	}
	if (all->key.keycode == D)
	{
		all->player.x += SPEED * cos((all->angle.alpha * PI / 180) + PI / 2);
		all->player.y += SPEED * sin((all->angle.alpha * PI / 180) + PI / 2);
	}
	if (all->key.keycode == ARROW_LEFT)
		all->angle.alpha -= SPEED * 2;
	if (all->key.keycode == ARROW_RIGHT)
		all->angle.alpha += SPEED * 2;
}

int		render_next_frame(t_all *all)
{
	create_map(all->file.map, all);
	create_player(all);
	reycast(all);
	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->data.img, 0, 0);
	if (all->key.keycode >= 0)
	{
		all->map_mass.x = 0;
		all->map_mass.y = 0;
		all->pix_for_map.x = 0;
		all->pix_for_map.y = 0;
		mlx_destroy_image(all->vars.mlx, all->data.img);
		all->data.img = mlx_new_image(all->vars.mlx, all->file.R_x, all->file.R_y);
		all->data.addr = mlx_get_data_addr(all->data.img, &all->data.bits_per_pixel, &all->data.line_length,
										   &all->data.endian);
		move(all);
		if (all->angle.alpha >= 360)
			all->angle.alpha = 0;
		else if (all->angle.alpha <= 0)
			all->angle.alpha = 360;
	}
	all->key.keycode = -1;
}

int ft_key_hook(int keycode, t_all *all)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(all->vars.mlx, all->vars.win);
		exit(-1);
	}
	if (keycode == W || keycode == S || keycode == A || keycode == D
	|| keycode == ARROW_LEFT || keycode == ARROW_RIGHT)
		all->key.keycode = keycode;
	return (0);
}

int ft_close_exit()
{
	exit(-1);
}

int ft_window(t_file file)
{
	t_vars	vars;
	t_data	img;
	t_all	all;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, file.R_x, file.R_y, "cub3d");
	img.img = mlx_new_image(vars.mlx, file.R_x, file.R_y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
	all.file = file;
	all.data = img;
	all.vars = vars;
	all.player.x = 0;
	all.player.y = 0;
	all.map_mass.x = 0;
	all.map_mass.y = 0;
	all.pix_for_map.x = 0;
	all.pix_for_map.y = 0;
	mlx_loop_hook(all.vars.mlx, render_next_frame, &all);
	mlx_hook(all.vars.win, 2, 1L << 0, ft_key_hook, &all);
	mlx_hook(all.vars.win, CLOSE, 0, ft_close_exit, &all);
	mlx_loop(all.vars.mlx);
	return (0);
}

int		main(int argc, char *argv[])
{
	t_file	file;
	//int		i;
	//i = 0;
	if (ft_open_file(argc, argv, &file) == -1)
		exit(-1);
	if (ft_check_init_file(&file) == -1)
		exit(-1);
	if (ft_window(file) == -1)
		exit(-1);
	full_free_file(&file);
}

	/*
	while (x != 100)
	{
		y = (149*x-50) / 99;
		mlx_pixel_put(mlx, mlx_win, x, y, 0x00ff0000);
		x++;
	}
012NSEW
*/

/*printf("x = %d\n", file.R_x);
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
		printf("map[%2d] = %s\n", i, file.map[i]);
		i++;
	}*/

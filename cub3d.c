/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:33:24 by dwanetta          #+#    #+#             */
/*   Updated: 2021/03/18 14:55:30 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>

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

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
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
			my_mlx_pixel_put(&all->map, x, y, color);
			y += 1;
		}
		x += 1;
	}
}

void create_map(char **map, t_all *all)
{
	int color;

	color = 0x00000000;
	while (map[all->map_mass.x] != NULL)
	{
		while (map[all->map_mass.x][all->map_mass.y] != '\0')
		{
			//------------map---------------
			if (map[all->map_mass.x][all->map_mass.y] == ' ')
				color = 0x00000000;
			if (map[all->map_mass.x][all->map_mass.y] == '1')
				color = 0x000FF000;
			if (map[all->map_mass.x][all->map_mass.y] == '0')
				color = 0x000FFFF0;
			//------------map---------------
			if ((map[all->map_mass.x][all->map_mass.y] == 'N' ||
			map[all->map_mass.x][all->map_mass.y] == 'S' ||
			map[all->map_mass.x][all->map_mass.y] == 'E' ||
			map[all->map_mass.x][all->map_mass.y] == 'W') &&
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
				all->player.x = all->map_mass.y * SIZE_CHUNK /*+ all->map_mass.y*/;
				all->player.y = all->map_mass.x * SIZE_CHUNK /*+ all->map_mass.x*/;
				map[all->map_mass.x][all->map_mass.y] = '0';
				color = 0x000FFFF0;
			}
			//------------map---------------
			print_kodred(all, SIZE_MAP, color, all->pix_for_map.x, all->pix_for_map.y);
			all->pix_for_map.x += SIZE_MAP;
			//all->pix_for_map.x++; //black line
			//------------mapend-------------
			all->map_mass.y++;
		}
		//------------map---------------
		all->pix_for_map.x = 0;
		//all->pix_for_map.y++; //black line
		all->pix_for_map.y += SIZE_MAP;
		//------------mapend-------------
		all->map_mass.x++;
		all->map_mass.y = 0;
	}
}

void print_player(t_all *all)
{
	int	tmp_y;
	int	tmp_x;

	tmp_y = (int)(all->player.y / SIZE_CHUNK * SIZE_MAP);
	tmp_x = (int)(all->player.x / SIZE_CHUNK * SIZE_MAP);
	print_kodred(all, SIZE_PLAYER, 0x00FF0000, tmp_x, tmp_y);
}

void print_floor_and_ceilling(t_all *all, int Y_up, int Y_down)
{

	if (Y_up != 0)
		while (Y_up >= 0)
		{
			my_mlx_pixel_put(&all->data, all->visual.width, Y_up,create_trgb(0, all->file.F[0], all->file.F[1],all->file.F[2]));
			Y_up--;
		}
	while (Y_down != all->file.R_y)
	{
		my_mlx_pixel_put(&all->data, all->visual.width, Y_down, create_trgb(0, all->file.C[0], all->file.C[1], all->file.C[2]));
		Y_down++;
	}
}

void print3d(t_all *all, double x, double y)
{
	double L;
	int Y_up;
	int Y_down;
	int H;
	int color;

	L = sqrt(pow((all->player.x - x), 2) + pow((all->player.y - y), 2));
	L *= cos(fabs(all->visual.ugl - (all->angle.alpha * PI / 180)));
	H = (int)round((SIZE_CHUNK / L) * all->visual.distC);
	Y_up = all->file.R_y / 2;
	Y_down = all->file.R_y / 2;
	color = (int)H + 220 / 220;
	color -=70;
	if (color >= 220)
		color = 220;
	if (color <= 50)
		color = 50;
	while (Y_up >= (all->file.R_y / 2) - (H / 2))
	{
		my_mlx_pixel_put(&all->data, all->visual.width, Y_up, create_trgb(0, color, color, color));
		if (Y_up == 0)
			break ;
		Y_up--;
	}
	while (Y_down <= (all->file.R_y / 2) + (H / 2))
	{
		if (Y_down == all->file.R_y)
			break ;
		my_mlx_pixel_put(&all->data, all->visual.width, Y_down, create_trgb(0, color, color, color));
		Y_down++;
	}
	print_floor_and_ceilling(all, Y_up, Y_down);

}

void print_line(t_all *all, double x1, double y1, double x2, double y2, int color)
{
	int deltaX;
	int deltaY;
	int length;
	double dX;
	double dY;

	deltaX = abs((int)(round(x1) - round(x2)));
	deltaY = abs((int)(round(y1) - round(y2)));
	length = MAX(deltaX, deltaY);
	if (length == 0)
	{
		//------------map---------------
		if (color == 0)
			my_mlx_pixel_put(&all->map, (int)round(x1 / SIZE_CHUNK * SIZE_MAP),  (int)round(y1 / SIZE_CHUNK * SIZE_MAP), color);
		//------------mapend-------------
		return ;
	}
	dX = (x2 - x1) / length;
	dY = (y2 - y1) / length;
	length++;
	while (length--)
	{
		x1 += dX;
		y1 += dY;
		if (all->file.map[(int)(round(y1) / SIZE_CHUNK)][(int)(round(x1) / SIZE_CHUNK)] == '1')
		{
			if (color != 0)//------------map---------------
				print3d(all, x1, y1);
			break;
		}
		//------------map---------------
		if (color == 0)
			my_mlx_pixel_put(&all->map, (int)round(x1 / SIZE_CHUNK * SIZE_MAP),  (int)round(y1 / SIZE_CHUNK * SIZE_MAP), color);
		//------------mapend-------------
	}
}

void reycast(t_all *all)
{
	double	x;
	double	y;

	all->visual.ugl = (all->angle.alpha - FOV / 2.0) * PI / 180;
	//all->visual.distC = (all->file.R_x / 2.0) * tan((FOV / 2.0) * PI / 180);
	all->visual.distC = (all->file.R_x / 2.0) / tan((FOV / 2.0) * PI / 180);
	all->visual.width = 0;
	while (all->visual.ugl <= ((all->angle.alpha + FOV / 2.0) * PI / 180))
	{
		x = (all->player.x) + (100000 * cos(all->visual.ugl));
		y = (all->player.y) + (100000 * sin(all->visual.ugl));
		print_line(all, (int)all->player.x, (int)all->player.y, (int)x, (int)y, 0x00FF0000);
		all->visual.ugl += (FOV * PI / 180) / (all->file.R_x - 1);
		all->visual.width++;
	}
	//------------map---------------
	x = (all->player.x) + (all->visual.distC * cos(all->angle.alpha * PI / 180));
	y = (all->player.y) + (all->visual.distC * sin(all->angle.alpha * PI / 180));
	print_line(all, (int)all->player.x, (int)all->player.y, (int)x, (int)y, 0x00000000);
	//------------mapend-------------
}

int		render_next_frame(t_all *all)
{
	create_map(all->file.map, all);
	print_player(all);//------------map---------------
	reycast(all);
	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->data.img, 0, 0);
	//------------map---------------
	if (all->key.map == 1)
		mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->map.img, 0, 0);
	//------------mapend-------------
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
		//------------map---------------
			mlx_destroy_image(all->vars.mlx, all->map.img);
			all->map.img = mlx_new_image(all->vars.mlx, 550, 250);
			all->map.addr = mlx_get_data_addr(all->map.img,
					&all->map.bits_per_pixel, &all->map.line_length,
					&all->map.endian);
		//------------mapend-------------
		move(all);
	}
	all->key.keycode = -1;
}

int myFPS(t_all *all)
{
	clock_t current_ticks, delta_ticks;
	clock_t fps = 0;
	current_ticks = clock();
	render_next_frame(all);
	delta_ticks = clock() - current_ticks;
	if(delta_ticks > 0)
		fps = CLOCKS_PER_SEC / delta_ticks;
	mlx_string_put(all->vars.mlx, all->vars.win, 5, 11, 0x00FF0000, ft_itoa(fps));
}

int ft_window(t_file file)
{
	t_all	all;
	t_data test;
	int width;
	int height;

	all.vars.mlx = mlx_init();
	all.vars.win = mlx_new_window(all.vars.mlx, file.R_x, file.R_y, "cub3d");
	all.data.img = mlx_new_image(all.vars.mlx, file.R_x, file.R_y);
	all.data.addr = mlx_get_data_addr(all.data.img, &all.data.bits_per_pixel, &all.data.line_length,
								 &all.data.endian);
	//------------map---------------
	all.map.img = mlx_new_image(all.vars.mlx, 550, 250);
	all.map.addr = mlx_get_data_addr(all.map.img, &all.map.bits_per_pixel, &all.map.line_length,
			&all.map.endian);
	all.key.map = 0;
	//------------mapend-------------
	all.file = file;
	all.player.x = 0;
	all.player.y = 0;
	all.map_mass.x = 0;
	all.map_mass.y = 0;
	all.pix_for_map.x = 0;
	all.pix_for_map.y = 0;
	test.img = mlx_xpm_file_to_image(all.vars.mlx, all.file.NO_texture, &width, &height);
	test.addr = mlx_get_data_addr(test.img, &test.bits_per_pixel, &test.line_length,
			&test.endian);
	//mlx_put_image_to_window(all.vars.mlx, all.vars.win, test.img, 0, 0);
	//printf("width = %d\nheight = %d\n", width, height);
	//mlx_loop_hook(all.vars.mlx, render_next_frame, &all);
	//mlx_loop_hook(all.vars.mlx, myFPS, &all);
	mlx_hook(all.vars.win, 2, 1L << 0, ft_key_hook, &all);
	mlx_hook(all.vars.win, CLOSE, 0, ft_close_exit, &all);
	mlx_loop(all.vars.mlx);

	return (0);
}

int		main(int argc, char *argv[])
{
	t_file	file;

	if (ft_open_file(argc, argv, &file) == -1)
		exit(-1);
	if (ft_check_init_file(&file) == -1)
		exit(-1);
	if (ft_window(file) == -1)
		exit(-1);
	full_free_file(&file);
}

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

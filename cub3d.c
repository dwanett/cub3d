/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:33:24 by dwanetta          #+#    #+#             */
/*   Updated: 2021/03/21 22:23:01 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>

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

void print_floor_and_ceilling(t_all *all, int floor, int ceilling)
{

	if (floor != 0)
		while (floor >= 0)
		{
			my_mlx_pixel_put(&all->data, all->visual.width, floor,create_trgb(0, all->file.F[0], all->file.F[1],all->file.F[2]));
			floor--;
		}
	if (ceilling != all->file.R_y)
		while (ceilling <= all->file.R_y)
		{
			my_mlx_pixel_put(&all->data, all->visual.width, ceilling, create_trgb(0, all->file.C[0], all->file.C[1], all->file.C[2]));
			ceilling++;
		}
}

void print3d(t_all *all, double x, double y)
{
	double L;
	int Y;
	int H;
	int H_real;
	int color;
	int i;
	int x_mass;
	int y_mass;

	L = sqrt(pow((all->player.x - x), 2) + pow((all->player.y - y), 2));
	L *= cos(fabs(all->visual.ugl - (all->angle.alpha * PI / 180)));
	H = (int)round((SIZE_CHUNK / L) * all->visual.distC);
	H_real = H;
	if (H > all->file.R_y)
		H = all->file.R_y;
	Y = (all->file.R_y / 2) - (H / 2);
	color = (int)H + 220 / 220;
	color -=70;
	if (color >= 220)
		color = 220;
	if (color <= 50)
		color = 50;
	print_floor_and_ceilling(all, Y, all->file.R_y);
	all->NO_texture.color_x = (int)x % SIZE_CHUNK;
	all->SO_texture.color_x = (int)x % SIZE_CHUNK;
	all->EA_texture.color_x = (int)y % SIZE_CHUNK;
	all->WE_texture.color_x = (int)y % SIZE_CHUNK;
	i = 0;
	x_mass = (int)(round(x) / SIZE_CHUNK);
	y_mass = (int)(round(y) / SIZE_CHUNK);
	x_mass *= SIZE_CHUNK;
	y_mass *= SIZE_CHUNK;
	while (Y <= (all->file.R_y / 2) + (H / 2) && Y <= all->file.R_y)
	{
		all->NO_texture.color_y = (int)(all->NO_texture.height * ((((H + H_real) >> 1) - i)) / H_real);
		all->SO_texture.color_y = (int)(all->SO_texture.height * ((((H + H_real) >> 1) - i)) / H_real);
		all->EA_texture.color_y = (int)(all->NO_texture.height * ((((H + H_real) >> 1) - i)) / H_real);
		all->WE_texture.color_y = (int)(all->SO_texture.height * ((((H + H_real) >> 1) - i)) / H_real);
		if (Y < 0)
			Y = 0;
		if ((y_mass + SIZE_CHUNK - 1 <= (int)round(y)) && (all->file.map[(y_mass / SIZE_CHUNK) + 1][x_mass / SIZE_CHUNK] == '0'))
			my_mlx_pixel_put(&all->data, all->visual.width, Y, (int)get_color_image(&all->NO_texture, (int)all->NO_texture.color_x, (int)all->NO_texture.color_y));
		else if ((y_mass == (int)round(y)) && (all->file.map[(y_mass / SIZE_CHUNK) - 1][x_mass / SIZE_CHUNK] == '0'))
			my_mlx_pixel_put(&all->data, all->visual.width, Y, (int)get_color_image(&all->SO_texture, (int)all->SO_texture.color_x, (int)all->SO_texture.color_y));
		else if ((x_mass + SIZE_CHUNK - 1 <= (int)round(x)) && (all->file.map[y_mass / SIZE_CHUNK][(x_mass / SIZE_CHUNK) + 1] == '0'))
			my_mlx_pixel_put(&all->data, all->visual.width, Y, (int)get_color_image(&all->EA_texture, (int)all->EA_texture.color_x, (int)all->EA_texture.color_y));
		else if ((x_mass == (int)round(x)) && (all->file.map[y_mass / SIZE_CHUNK][(x_mass / SIZE_CHUNK) - 1] == '0'))
			my_mlx_pixel_put(&all->data, all->visual.width, Y, (int)get_color_image(&all->WE_texture, (int)all->WE_texture.color_x, (int)all->WE_texture.color_y));
		Y++;
		i++;
	}
	print_floor_and_ceilling(all, 0, Y);
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
			my_mlx_pixel_put(&all->map, (int)round(x1 / SIZE_CHUNK * SIZE_MAP),  (int)round(y1 / SIZE_CHUNK * SIZE_MAP), all->SO_texture.color_y);
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
		x = (all->player.x) + (10000 * cos(all->visual.ugl));
		y = (all->player.y) + (10000 * sin(all->visual.ugl));
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
	all.NO_texture.img = mlx_xpm_file_to_image(all.vars.mlx, all.file.NO_texture, &all.NO_texture.width, &all.NO_texture.height);
	all.NO_texture.addr = mlx_get_data_addr(all.NO_texture.img, &all.NO_texture.bits_per_pixel, &all.NO_texture.line_length,
			&all.NO_texture.endian);
	all.SO_texture.img = mlx_xpm_file_to_image(all.vars.mlx, all.file.SO_texture, &all.SO_texture.width, &all.SO_texture.height);
	all.SO_texture.addr = mlx_get_data_addr(all.SO_texture.img, &all.SO_texture.bits_per_pixel, &all.SO_texture.line_length,
			&all.SO_texture.endian);
	all.WE_texture.img = mlx_xpm_file_to_image(all.vars.mlx, all.file.WE_texture, &all.WE_texture.width, &all.WE_texture.height);
	all.WE_texture.addr = mlx_get_data_addr(all.WE_texture.img, &all.WE_texture.bits_per_pixel, &all.WE_texture.line_length,
			&all.WE_texture.endian);
	all.EA_texture.img = mlx_xpm_file_to_image(all.vars.mlx, all.file.EA_texture, &all.EA_texture.width, &all.EA_texture.height);
	all.EA_texture.addr = mlx_get_data_addr(all.EA_texture.img, &all.EA_texture.bits_per_pixel, &all.EA_texture.line_length,
			&all.EA_texture.endian);
	mlx_loop_hook(all.vars.mlx, myFPS, &all);
	mlx_put_image_to_window(all.vars.mlx, all.vars.win, all.data.img, 0, 0);
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

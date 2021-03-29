/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:33:24 by dwanetta          #+#    #+#             */
/*   Updated: 2021/03/24 13:27:08 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_floor_and_ceilling(t_all *all, int floor, int ceilling)
{
	if (floor != 0)
		while (floor >= 0)
		{
			my_mlx_pixel_put(&all->data, all->visual.width, floor,
			create_trgb(0, all->file.F[0], all->file.F[1], all->file.F[2]));
			floor--;
		}
	if (ceilling != all->file.R_y)
		while (ceilling <= all->file.R_y)
		{
			my_mlx_pixel_put(&all->data, all->visual.width, ceilling,
			create_trgb(0, all->file.C[0], all->file.C[1], all->file.C[2]));
			ceilling++;
		}
}

void	put_pix_texture(t_all *all, t_maping_texture *texture)
{
	if ((texture->y_mass + SIZE_CHUNK - 1 <= (int)round(texture->y)) &&
			(all->file.map[(texture->y_mass / SIZE_CHUNK) + 1]
			[texture->x_mass / SIZE_CHUNK] == '0'))
		my_mlx_pixel_put(&all->data, all->visual.width, texture->y_tmp,
			(int)get_color_image(&all->NO_texture,
			(int)all->NO_texture.color_x, (int)all->NO_texture.color_y));
	else if ((texture->y_mass == (int)round(texture->y)) &&
			 (all->file.map[(texture->y_mass / SIZE_CHUNK) - 1]
			[texture->x_mass / SIZE_CHUNK] == '0'))
		my_mlx_pixel_put(&all->data, all->visual.width, texture->y_tmp,
			(int)get_color_image(&all->SO_texture,
			(int)all->SO_texture.color_x, (int)all->SO_texture.color_y));
	else if ((texture->x_mass + SIZE_CHUNK - 1 <= (int)round(texture->x)) &&
			 (all->file.map[texture->y_mass / SIZE_CHUNK]
			[(texture->x_mass / SIZE_CHUNK) + 1] == '0'))
		my_mlx_pixel_put(&all->data, all->visual.width, texture->y_tmp,
			(int)get_color_image(&all->EA_texture,
			(int)all->EA_texture.color_x, (int)all->EA_texture.color_y));
	else if ((texture->x_mass == (int)round(texture->x)) &&
			 (all->file.map[texture->y_mass / SIZE_CHUNK]
			[(texture->x_mass / SIZE_CHUNK) - 1] == '0'))
		my_mlx_pixel_put(&all->data, all->visual.width, texture->y_tmp,
			(int)get_color_image(&all->WE_texture,
			(int)all->WE_texture.color_x, (int)all->WE_texture.color_y));
}

void	init_sprite(t_all *all, double x, double y)
{
	all->sprite.yes = 1;
	all->sprite.x = x;
	all->sprite.dist = sqrt(pow((all->player.x - x), 2) + pow((all->player.y - y), 2));
	all->sprite.dist *= cos(fabs(all->visual.ugl - (all->angle.alpha * PI180)));
	all->sprite.h = (int)round((SIZE_CHUNK / all->sprite.dist) * all->visual.distC);
	all->sprite.h_real = all->sprite.h;
	if (all->sprite.h > all->file.R_y)
		all->sprite.h = all->file.R_y;
	all->sprite.y_tmp = (all->file.R_y / 2) - (all->sprite.h / 2);
}

void	put_texture(t_all *all, t_maping_texture *texture, int h, int h_real)
{
	int k;
	int i;

	i = 0;
	all->NO_texture.color_x = (int)texture->x % SIZE_CHUNK;
	all->SO_texture.color_x = (int)texture->x % SIZE_CHUNK;
	all->EA_texture.color_x = (int)texture->y % SIZE_CHUNK;
	all->WE_texture.color_x = (int)texture->y % SIZE_CHUNK;
	print_floor_and_ceilling(all, texture->y_tmp, all->file.R_y);
	while (texture->y_tmp <= (all->file.R_y / 2) + (h / 2) &&
		   texture->y_tmp <= all->file.R_y)
	{
		k = ((h + h_real) >> 1) - i;
		all->NO_texture.color_y = (int)(all->NO_texture.height * k / h_real);
		all->SO_texture.color_y = (int)(all->SO_texture.height * k / h_real);
		all->EA_texture.color_y = (int)(all->EA_texture.height * k / h_real);
		all->WE_texture.color_y = (int)(all->WE_texture.height * k / h_real);
		//put_pix_texture(all, texture);
		my_mlx_pixel_put(&all->data, all->visual.width, texture->y_tmp, 0x00FFFFFF);
		texture->y_tmp++;
		i++;
	}
	/*while (all->sprite.y_tmp <= (all->file.R_y / 2) + (all->sprite.h / 2) &&
			all->sprite.y_tmp <= all->file.R_y && all->sprite.yes)
	{
		all->S_texture.color_y = (int)(all->S_texture.height * k / all->sprite.h_real);
		my_mlx_pixel_put(&all->data, all->visual.width, all->sprite.y_tmp,
				(int)get_color_image(&all->S_texture,
						(int)all->S_texture.color_x, (int)all->S_texture.color_y));
		all->sprite.y_tmp++;

	}*/
	print_floor_and_ceilling(all, 0, texture->y_tmp);
}

void	print3d(t_all *all, double x, double y, double l)
{
	t_maping_texture	texture;
	int					h;
	int					h_real;

	l *= cos(fabs(all->visual.ugl - (all->angle.alpha * PI180)));
	h = (int)round((SIZE_CHUNK / l) * all->visual.distC);
	h_real = h;
	if (h > all->file.R_y)
		h = all->file.R_y;
	texture.y_tmp = (all->file.R_y / 2) - (h / 2);
	texture.x_mass = (int)(round(x) / SIZE_CHUNK) * SIZE_CHUNK;
	texture.y_mass = (int)(round(y) / SIZE_CHUNK) * SIZE_CHUNK;
	texture.x = x;
	texture.y = y;
	put_texture(all, &texture, h, h_real);
}
//
//void	dda(t_all *all, double x2, double y2, int length)
//{
//	double	dx;
//	double	dy;
//	double	x1;
//	double	y1;
//
//	x1 = all->player.x;
//	y1 = all->player.y;
//	if (length == 0)
//		return ;
//	dx = (x2 - all->player.x) / length;
//	dy = (y2 - all->player.y) / length++;
//	while (length--)
//	{
//		if (all->file.map[(int)(round((y1 += dy)) / SIZE_CHUNK)]
//						[(int)(round((x1 += dx)) / SIZE_CHUNK)] == '1')
//		{
//			if (all->visual.color != 0)*//*------------map---------------*//*
//				print3d(all, x1, y1);
//			all->sprite.yes = 0;
//			break ;
//
//		}
//		if (all->file.map[(int)(round(y1) / SIZE_CHUNK)]
//			 [(int)(round(x1) / SIZE_CHUNK)] == '2')
//			init_sprite(all, x1, y1);
//		if (all->visual.color == 0)*//*------------map---------------*//*
//			my_mlx_pixel_put(&all->map, (int)round(x1 / SIZE_CHUNK * SIZE_MAP),
//					(int)round(y1 / SIZE_CHUNK * SIZE_MAP), all->visual.color);
//		*//*------------mapend-------------*//*
//	}
//}
//
//void	reycast(t_all *all)
//{
//	double	x;
//	double	y;
//
//	all->visual.ugl = (all->angle.alpha - (int)FOV2) * PI180;
//	//all->visual.distC = (all->file.R_x / 2.0) * tan((int)FOV2 * PI180);
//	all->visual.distC = (all->file.R_x / 2.0) / tan((int)FOV2 * PI180);
//	all->visual.width = 0;
//	all->visual.color = 0x00FF0000;
//	while (all->visual.ugl <= ((all->angle.alpha + (int)FOV2) * PI180))
//	{
//		x = all->player.x + (10000 * cos(all->visual.ugl));
//		y = all->player.y + (10000 * sin(all->visual.ugl));
//		dda(all, (int)x, (int)y,
//		MAX(abs((int)(round(all->player.x) - round(x))),
//		abs((int)(round(all->player.y) - round(y)))));
//		all->visual.ugl += (FOV * PI180) / (all->file.R_x - 1);
//		all->visual.width++;
//	}
//	all->visual.color = 0x00000000;
//	//------------map---------------
//	x = (all->player.x) + (all->visual.distC * cos(all->angle.alpha * PI180));
//	y = (all->player.y) + (all->visual.distC * sin(all->angle.alpha * PI180));
//	dda(all, (int)x, (int)y,
//	MAX(abs((int)(round(all->player.x) - round(x))),
//	abs((int)(round(all->player.y) - round(y)))));
//	//------------mapend------------
//}

void	dda(t_all *all, double x2, double y2, int length)
{
	double	dx;
	double	dy;
	double	x1;
	double	y1;

	x1 = all->player.x;
	y1 = all->player.y;
	if (length == 0)
		return ;
	dx = (x2 - all->player.x) / length;
	dy = (y2 - all->player.y) / length++;
	while (length--)
	{
		y1 += dy;
		x1 += dx;
		my_mlx_pixel_put(&all->map, (int)round(x1 / SIZE_CHUNK * SIZE_MAP),
					(int)round(y1 / SIZE_CHUNK * SIZE_MAP), all->visual.color);
	}
}

void	reycast(t_all *all)
{
	t_reycast	horiz;
	t_reycast	verti;
	t_posi		tmp;
	double		cos_a;
	double		sin_a;

	all->visual.ugl = (all->angle.alpha - (int)FOV2) * PI180;
	//all->visual.ugl = all->angle.alpha * PI180;
	all->visual.distC = (all->file.R_x / 2.0) / tan((int) FOV2 * PI180);
	all->visual.width = 0;
	all->visual.color = 0x00000000;
	tmp.x = (all->player.x) + (16 * cos(all->angle.alpha * PI180));
	tmp.y = (all->player.y) + (16 * sin(all->angle.alpha * PI180));
	dda(all, (int) tmp.x, (int) tmp.y,
			MAX(abs((int) (round(all->player.x) - round(tmp.x))),
					abs((int) (round(all->player.y) - round(tmp.y)))));
	while (all->visual.ugl <= ((all->angle.alpha + (int)FOV2) * PI180))
	{
		tmp.x = all->player.x;
		tmp.y = all->player.y;
		verti.gip = all->player.y;
		horiz.gip = all->player.x;
		cos_a = cos(all->visual.ugl);
		sin_a = sin(all->visual.ugl);
		if (cos_a >= 0)
			verti.raz = 1;
		else
			verti.raz = -1;
		if (sin_a >= 0)

			horiz.raz = 1;
		else
			horiz.raz = -1;
		while (1)
		{
			verti.dist_x = floor(tmp.x / SIZE_CHUNK) * SIZE_CHUNK + (verti.raz * SIZE_CHUNK);
			if (cos_a < 0)
				verti.dist_x += SIZE_CHUNK - SIZE_PLAYER;
			verti.dist = fabs(verti.dist_x - tmp.x) / cos_a;
			verti.gip += (verti.dist * sin(all->visual.ugl) * (verti.raz));
			if (verti.gip < 0 || verti.dist_x < 0 || (verti.gip / SIZE_CHUNK >= all->map_mass.max_x))
				break;
			if (all->file.map[(int)(floor(verti.gip) / SIZE_CHUNK)]
			[(int)(floor(verti.dist_x) / SIZE_CHUNK)] == '1')
				break;
			tmp.x = verti.dist_x;
		}
		while (1)
		{
			horiz.dist_y = floor((tmp.y / SIZE_CHUNK)) * SIZE_CHUNK + (horiz.raz * SIZE_CHUNK);
			if (sin_a < 0)
				horiz.dist_y += SIZE_CHUNK - SIZE_PLAYER;
			horiz.dist = fabs(horiz.dist_y - tmp.y) / sin_a;
			horiz.gip += (	horiz.dist * cos(all->visual.ugl) * (horiz.raz));
			if (horiz.dist_y < 0 || horiz.gip < 0 || (horiz.gip / SIZE_CHUNK >= all->map_mass.max_y) || (horiz.dist_y / SIZE_CHUNK >= all->map_mass.max_x))
				break;
			if (all->file.map[(int) (floor(horiz.dist_y) / SIZE_CHUNK)]
			[(int)(floor(horiz.gip) / SIZE_CHUNK)] == '1')
				break;
			tmp.y = horiz.dist_y;
		}
		horiz.l = sqrt(pow((all->player.x - horiz.gip), 2) + pow((all->player.y - horiz.dist_y), 2));
		verti.l = sqrt(pow((all->player.x - verti.dist_x), 2) + pow((all->player.y - verti.gip), 2));
		if (fabs(horiz.l) <= fabs(verti.l))
		{
			print3d(all, horiz.gip, horiz.dist_y, horiz.l);
			//print_kodred(all, 3, 0x00FF0000, (int)(gip_h / SIZE_CHUNK * SIZE_MAP), (int)(dist_h_y / SIZE_CHUNK * SIZE_MAP));
			dda(all, (int)horiz.gip, (int)horiz.dist_y + 1,
			MAX(abs((int)(round(all->player.x) - round(horiz.gip))),
			abs((int)(round(all->player.y) - round(horiz.dist_y + 1)))));
		}
		else
		{
			print3d(all, verti.dist_x, verti.gip, verti.l);
			//print_kodred(all, 3, 0x00FF0000, (int)(dist_v_x / SIZE_CHUNK * SIZE_MAP), (int)(gip_v / SIZE_CHUNK * SIZE_MAP));
			dda(all, (int)verti.dist_x, (int)verti.gip,
					MAX(abs((int)(round(all->player.x) - round(verti.dist_x))),
							abs((int)(round(all->player.y) - round(verti.gip)))));
		}
		all->visual.ugl += (FOV * PI180) / (all->file.R_x - 1);
		all->visual.width++;
	}
}

int		render_next_frame(t_all *all)
{
	create_map(all->file.map, all);
	print_player(all);/*------------map---------------*/
	reycast(all);
	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->data.img, 0, 0);
	/*------------map---------------*/
	if (all->key.map == 1)
		mlx_put_image_to_window(all->vars.mlx, all->vars.win,
		all->map.img, 0, 0);
	/*------------mapend------------*/
	if (all->key.keycode >= 0)
	{
		all->map_mass.x = 0;
		all->map_mass.y = 0;
		all->map_mass.max_x = 0;
		all->map_mass.max_y = 0;
		all->pix_for_map.x = 0;
		all->pix_for_map.y = 0;
		mlx_destroy_image(all->vars.mlx, all->data.img);
		all->data.img = mlx_new_image(all->vars.mlx,
		all->file.R_x, all->file.R_y);
		all->data.addr = mlx_get_data_addr(all->data.img,
		&all->data.bits_per_pixel, &all->data.line_length,
		&all->data.endian);
		/*------------map---------------*/
		mlx_destroy_image(all->vars.mlx, all->map.img);
		all->map.img = mlx_new_image(all->vars.mlx, 550, 250);
		all->map.addr = mlx_get_data_addr(all->map.img,
		&all->map.bits_per_pixel, &all->map.line_length,
		&all->map.endian);
		/*------------mapend------------*/
		move(all);
	}
	all->key.keycode = -1;
	return (0);
}

void	init_all_help(t_all *all)
{
	all->NO_texture.addr = mlx_get_data_addr(all->NO_texture.img,
	&all->NO_texture.bits_per_pixel, &all->NO_texture.line_length,
	&all->NO_texture.endian);
	all->SO_texture.addr = mlx_get_data_addr(all->SO_texture.img,
	&all->SO_texture.bits_per_pixel, &all->SO_texture.line_length,
	&all->SO_texture.endian);
	all->WE_texture.addr = mlx_get_data_addr(all->WE_texture.img,
	&all->WE_texture.bits_per_pixel, &all->WE_texture.line_length,
	&all->WE_texture.endian);
	all->EA_texture.addr = mlx_get_data_addr(all->EA_texture.img,
	&all->EA_texture.bits_per_pixel, &all->EA_texture.line_length,
	&all->EA_texture.endian);
	all->S_texture.addr = mlx_get_data_addr(all->S_texture.img,
	&all->S_texture.bits_per_pixel, &all->S_texture.line_length,
	&all->S_texture.endian);
}

int		init_all(t_all *all)
{
	all->sprite.yes = 0;
	all->player.x = 0;
	all->player.y = 0;
	all->map_mass.x = 0;
	all->map_mass.y = 0;
	all->map_mass.max_x = 0;
	all->map_mass.max_y = 0;
	all->pix_for_map.x = 0;
	all->pix_for_map.y = 0;
	all->NO_texture.img = mlx_xpm_file_to_image(all->vars.mlx,
	all->file.NO_texture, &all->NO_texture.width, &all->NO_texture.height);
	all->SO_texture.img = mlx_xpm_file_to_image(all->vars.mlx,
	all->file.SO_texture, &all->SO_texture.width, &all->SO_texture.height);
	all->WE_texture.img = mlx_xpm_file_to_image(all->vars.mlx,
	all->file.WE_texture, &all->WE_texture.width, &all->WE_texture.height);
	all->EA_texture.img = mlx_xpm_file_to_image(all->vars.mlx,
	all->file.EA_texture, &all->EA_texture.width, &all->EA_texture.height);
	all->S_texture.img = mlx_xpm_file_to_image(all->vars.mlx,
	all->file.S_texture, &all->S_texture.width, &all->S_texture.height);
	if (all->NO_texture.img == NULL || all->SO_texture.img == NULL ||
	all->WE_texture.img == NULL || all->EA_texture.img == NULL ||
	all->S_texture.img == NULL)
	{
		print_error_img(all);
		return (-1);
	}
	init_all_help(all);
	return (0);
}

int		ft_window(t_file file)
{
	t_all	all;

	if ((all.vars.mlx = mlx_init()) == NULL)
	{
		ft_putstr_fd("Error\nLibrary initialization mlx.\n", 1);
		return (-1);
	}
	all.vars.win = mlx_new_window(all.vars.mlx, file.R_x, file.R_y, "cub3d");
	all.data.img = mlx_new_image(all.vars.mlx, file.R_x, file.R_y);
	all.data.addr = mlx_get_data_addr(all.data.img,
	&all.data.bits_per_pixel, &all.data.line_length, &all.data.endian);
	/*------------map---------------*/
	all.map.img = mlx_new_image(all.vars.mlx, 550, 500);
	all.map.addr = mlx_get_data_addr(all.map.img,
	&all.map.bits_per_pixel, &all.map.line_length, &all.map.endian);
	all.key.map = 0;
	/*------------mapend------------*/
	all.file = file;
	if (init_all(&all) == -1)
		return (-1);
	mlx_loop_hook(all.vars.mlx, myFPS, &all);
	//mlx_loop_hook(all.vars.mlx, render_next_frame, &all);
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

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

void		print_floor_and_ceilling(t_all *all, int ceilling, int floor)
{
	if (ceilling != 0)
		while (ceilling >= 0)
		{
			my_mlx_pixel_put(&all->data, all->visual.width, ceilling,
			create_trgb(0, all->file.C[0], all->file.C[1], all->file.C[2]));
			ceilling--;
		}
	if (floor != all->file.R_y)
		while (floor <= all->file.R_y)
		{
			my_mlx_pixel_put(&all->data, all->visual.width, floor,
			create_trgb(0, all->file.F[0], all->file.F[1], all->file.F[2]));
			floor++;
		}
}

/*void	put_pix_texture(t_all *all, t_maping_texture *texture)
{
	if ((texture->y_mass + SIZE_CHUNK - SIZE_PLAYER == (int)round(texture->y) &&
		(all->file.map[(texture->y_mass / SIZE_CHUNK) + 1]
		 [texture->x_mass / SIZE_CHUNK] == '0')))
			my_mlx_pixel_put(&all->data, all->visual.width, texture->y_tmp,
			(int)get_color_image(&all->NO_texture,
			(int)all->NO_texture.color_x, (int)all->NO_texture.color_y));
	else if ((texture->y_mass == (int)round(texture->y)) &&
			 (all->file.map[(texture->y_mass / SIZE_CHUNK) - 1]
			[texture->x_mass / SIZE_CHUNK] == '0'))
		my_mlx_pixel_put(&all->data, all->visual.width, texture->y_tmp,
			(int)get_color_image(&all->SO_texture,
			(int)all->SO_texture.color_x, (int)all->SO_texture.color_y));
	else if ((texture->x_mass + SIZE_CHUNK - SIZE_PLAYER <= (int)round(texture->x)) &&
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
}*/

void		put_pix_texture(t_all *all, t_maping_texture *texture)
{
	if ((texture->y_mass + SIZE_CHUNK - SIZE_PLAYER == (int)round(texture->y)))
		my_mlx_pixel_put(&all->data, all->visual.width, texture->y_tmp,
		(int)get_color_image(&all->NO_texture,
		(int)all->NO_texture.color_x, (int)all->NO_texture.color_y));
	else if (texture->y_mass == (int)round(texture->y))
		my_mlx_pixel_put(&all->data, all->visual.width, texture->y_tmp,
		(int)get_color_image(&all->SO_texture,
		(int)all->SO_texture.color_x, (int)all->SO_texture.color_y));
	else if ((texture->x_mass + SIZE_CHUNK - SIZE_PLAYER <= (int)round(texture->x)))
		my_mlx_pixel_put(&all->data, all->visual.width, texture->y_tmp,
		(int)get_color_image(&all->EA_texture,
		(int)all->EA_texture.color_x, (int)all->EA_texture.color_y));
	else if (texture->x_mass == (int)round(texture->x))
		my_mlx_pixel_put(&all->data, all->visual.width, texture->y_tmp,
		(int)get_color_image(&all->WE_texture,
		(int)all->WE_texture.color_x, (int)all->WE_texture.color_y));
}

int			check(double n1, double n2)
{
	if (n1 > n2)
		return (0);
	else
		return (1);
}

t_sprite*	sort_list(t_sprite *head)
{
	t_sprite	*q;
	t_sprite	*out;
	t_sprite	*p;
	t_sprite	*pr;

	out = NULL;
	while (head !=NULL)
	{
  		q = head;
  		head = head->next;
		p = out, pr = NULL;
		while (p != NULL && check(q->dist,p->dist) > 0)
			pr = p, p = p->next;
		if (pr == NULL)
		{
			q->next = out;
			out = q;
		}
		else
		{
			q->next = p;
			pr->next = q;
		}
 	}
	return out;
}

void		print_curr_sprite(t_all *all)
{
	int 	j;
	int 	i;

	i = -1;
	while (i < all->sprite->size)
	{
		i++;
		if (all->sprite->start + i < 0 ||
			all->sprite->start + i >= all->file.R_x ||
			all->visual.rey_len[all->sprite->start + i] < all->sprite->dist)
			continue ;
		j = -1;
		while (j < all->sprite->size - 1)
		{
			j++;
			if (all->sprite->y_start + j < 0 ||
				all->sprite->y_start + j >= all->file.R_y)
				continue ;
			my_mlx_pixel_put(&all->data,(int) (all->sprite->start + i),
			(int)(all->sprite->y_start + j),
			(int)get_color_image(&all->S_texture, (int)(i * all->S_texture.width /
			all->sprite->size),(int) (j * all->S_texture.height /
			all->sprite->size)));
		}
	}
}

void		print_sprite(t_all *all)
{
	t_sprite	*tmp;

	tmp = all->sprite;
	while (all->sprite != NULL)
	{
		print_curr_sprite(all);
		all->sprite = all->sprite->next;
	}
	all->sprite = tmp;
}

void		init_sprite(t_all *all, double step)
{
	t_sprite		*tmp;
	double			teta;

	tmp = all->sprite;
	while (all->sprite != NULL)
	{
		teta = atan2(all->sprite->y - all->player.y,
				all->sprite->x - all->player.x);
		all->sprite->dist = sqrt(pow(all->sprite->x - all->player.x, 2) +
								pow(all->sprite->y - all->player.y, 2));
		//all->sprite->dist *= cos(fabs((all->angle.alpha * PI180) - teta));
		while (teta - (all->angle.alpha * PI180) > PI)
			teta -= 2 * PI;
		while (teta - (all->angle.alpha * PI180) < -PI)
			teta += 2 * PI;
		all->sprite->size = (int)round(((SIZE_CHUNK / SCALE) /
		all->sprite->dist) * all->visual.distC);
		all->sprite->start = (int)((all->file.R_x - 1) / 2.0 +
		(teta - (all->angle.alpha * PI180)) / step - all->sprite->size / 2.0);
		all->sprite->y_start = (all->file.R_y / 2) + (all->sprite->size / SIZE_CHUNK);
		all->sprite = all->sprite->next;
	}
	all->sprite = tmp;
	all->sprite = sort_list(all->sprite);
	print_sprite(all);
	all->visual.sprite_yes = 0;
}

void		put_texture_help(t_all *all, t_maping_texture *texture)
{
	if (SIZE_CHUNK > all->NO_texture.width)
		all->NO_texture.color_x = (int)(((int)texture->x % SIZE_CHUNK) /
										(SIZE_CHUNK / all->NO_texture.width));
	else
		all->NO_texture.color_x = (int)(((int)texture->x % SIZE_CHUNK) *
										(all->NO_texture.width / SIZE_CHUNK));
	if (SIZE_CHUNK > all->SO_texture.width)
		all->SO_texture.color_x = (int)(((int)texture->x % SIZE_CHUNK) /
										(SIZE_CHUNK / all->SO_texture.width));
	else
		all->SO_texture.color_x = (int)(((int)texture->x % SIZE_CHUNK) *
										(all->SO_texture.width / SIZE_CHUNK));
	if (SIZE_CHUNK > all->EA_texture.width)
		all->EA_texture.color_x = (int)(((int)texture->y % SIZE_CHUNK) /
										(SIZE_CHUNK / all->EA_texture.width));
	else
		all->EA_texture.color_x = (int)(((int)texture->y % SIZE_CHUNK) *
										(all->EA_texture.width / SIZE_CHUNK));
	if (SIZE_CHUNK > all->WE_texture.width)
		all->WE_texture.color_x = (int)(((int)texture->y % SIZE_CHUNK) /
										(SIZE_CHUNK / all->WE_texture.width));
	else
		all->WE_texture.color_x = (int)(((int)texture->y % SIZE_CHUNK) *
										(all->WE_texture.width / SIZE_CHUNK));
}

void		put_texture(t_all *all, t_maping_texture *texture, int h, int h_real)
{
	int k;
	int i;

	i = 0;
	put_texture_help(all, texture);
	print_floor_and_ceilling(all, 0, texture->y_tmp);
	while (texture->y_tmp >= (all->file.R_y / 2) - (h / 2) &&
		   texture->y_tmp >= 0)
	{
		k = ((h + h_real) >> 1) - i;
		all->NO_texture.color_y = (int)(all->NO_texture.height * k / h_real);
		all->SO_texture.color_y = (int)(all->SO_texture.height * k / h_real);
		all->EA_texture.color_y = (int)(all->EA_texture.height * k / h_real);
		all->WE_texture.color_y = (int)(all->WE_texture.height * k / h_real);
		put_pix_texture(all, texture);
		//my_mlx_pixel_put(&all->data, all->visual.width, texture->y_tmp, 0x00FFFFFF);
		texture->y_tmp--;
		i++;
	}
	print_floor_and_ceilling(all, texture->y_tmp, all->file.R_y);
}

void	print3d(t_all *all, double x, double y, double l)
{
	t_maping_texture	texture;
	int					h;
	int					h_real;

	all->visual.rey_len[all->visual.width] = l;
	l *= cos(fabs(all->visual.ugl - (all->angle.alpha * PI180)));
	h = (int)round((SIZE_CHUNK / l) * all->visual.distC);
	h_real = h;
	if (h > all->file.R_y)
		h = all->file.R_y;
	texture.y_tmp = (all->file.R_y / 2) + (h / 2);
	texture.x_mass = (int)(round(x) / SIZE_CHUNK) * SIZE_CHUNK;
	texture.y_mass = (int)(round(y) / SIZE_CHUNK) * SIZE_CHUNK;
	texture.x = x;
	texture.y = y;
	put_texture(all, &texture, h, h_real);
}

void	reycast(t_all *all)
{
	t_reycast	horiz;
	t_reycast	verti;
	t_posi		tmp;
	double		cos_a;
	double		sin_a;
	double		step;

	all->visual.ugl = (all->angle.alpha - (int)FOV2) * PI180;
	all->visual.distC = (all->file.R_x/ 2.0) / tan((int) FOV2 * PI180);
	all->visual.width = 0;
	step = (FOV * PI180) / (all->file.R_x - 1);
	while (all->visual.ugl <= ((all->angle.alpha + (int)FOV2) * PI180))
	{
		tmp.x = all->player.x;
		tmp.y = all->player.y;
		horiz.gip = all->player.x;
		cos_a = cos(all->visual.ugl);
		sin_a = sin(all->visual.ugl);
		if (cos_a >= 0)
		{
			verti.gip = all->player.y;
			horiz.gip = all->player.x;
			verti.raz = 1;
		}
		else
		{
			verti.gip = all->player.y + SIZE_PLAYER;
			horiz.gip = all->player.x + SIZE_PLAYER;
			verti.raz = -1;
		}
		if (sin_a >= 0)
		{
			horiz.gip = all->player.x;
			verti.gip = all->player.y;
			horiz.raz = 1;
		}
		else
		{
			verti.gip = all->player.y + SIZE_PLAYER;
			horiz.gip = all->player.x + SIZE_PLAYER;
			horiz.raz = -1;
		}
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
			if (all->file.map[(int)(floor(verti.gip) / SIZE_CHUNK)]
				[(int)(floor(verti.dist_x) / SIZE_CHUNK)] == '2')
				all->visual.sprite_yes = 1;
			tmp.x = verti.dist_x;
		}
		while (1)
		{
			horiz.dist_y = floor((tmp.y / SIZE_CHUNK)) * SIZE_CHUNK + (horiz.raz * SIZE_CHUNK);
			if (sin_a < 0)
				horiz.dist_y += SIZE_CHUNK - SIZE_PLAYER;
			horiz.dist = fabs(horiz.dist_y - tmp.y) / sin_a;
			horiz.gip += (horiz.dist * cos(all->visual.ugl) * (horiz.raz));
			if (horiz.dist_y < 0 || horiz.gip < 0 || (horiz.gip / SIZE_CHUNK >= all->map_mass.max_y) || (horiz.dist_y / SIZE_CHUNK >= all->map_mass.max_x))
				break;
			if (all->file.map[(int) (floor(horiz.dist_y) / SIZE_CHUNK)]
			[(int)(floor(horiz.gip) / SIZE_CHUNK)] == '1')
				break;
			if (all->file.map[(int) (floor(horiz.dist_y) / SIZE_CHUNK)]
				[(int)(floor(horiz.gip) / SIZE_CHUNK)] == '2')
				all->visual.sprite_yes = 1;
			tmp.y = horiz.dist_y;
		}
		horiz.l = sqrt(pow((all->player.x - horiz.gip), 2) + pow((all->player.y - horiz.dist_y), 2));
		verti.l = sqrt(pow((all->player.x - verti.dist_x), 2) + pow((all->player.y - verti.gip), 2));
		if (fabs(horiz.l) < fabs(verti.l))
			print3d(all, horiz.gip, horiz.dist_y, horiz.l);
		else
			print3d(all, verti.dist_x, verti.gip, verti.l);
		all->visual.ugl += step;
		all->visual.width++;
	}
	if (all->visual.sprite_yes == 1)
		init_sprite(all, step);
}

int		render_next_frame(t_all *all)
{
	print_player(all);/*------------map---------------*/
	reycast(all);
	if (all->file.check_save_image == 1)
	{
		create_bmp(all);
		ft_close_exit(all);
	}
	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->data.img, 0, 0);
	/*------------map---------------*/
	if (all->key.map == 1)
	{
		mlx_put_image_to_window(all->vars.mlx, all->vars.win,
				all->map.img, 0, 0);
		mlx_put_image_to_window(all->vars.mlx, all->vars.win,
		all->pl.img, (int)(all->player.x / SIZE_CHUNK * SIZE_MAP),
		(int)(all->player.y / SIZE_CHUNK * SIZE_MAP));
	}
	/*------------mapend------------*/
	if (all->key.keycode >= 0)
	{
		mlx_destroy_image(all->vars.mlx, all->data.img);
		all->data.img = mlx_new_image(all->vars.mlx,
		all->file.R_x, all->file.R_y);
		all->data.addr = mlx_get_data_addr(all->data.img,
		&all->data.bits_per_pixel, &all->data.line_length,
		&all->data.endian);
		/*------------map---------------*/
		mlx_destroy_image(all->vars.mlx, all->pl.img);
		all->pl.img = mlx_new_image(all->vars.mlx,
				SIZE_PLAYER, SIZE_PLAYER);
		all->pl.addr = mlx_get_data_addr(all->pl.img,
				&all->pl.bits_per_pixel, &all->pl.line_length,
				&all->pl.endian);
		/*------------mapend------------*/
		move(all);
	}
	all->key.keycode = -1;
	return (0);
}

int		ft_window(t_file file)
{
	t_all	all;
	int 	real_size_x;
	int 	real_size_y;

	if ((all.vars.mlx = mlx_init()) == NULL)
	{
		ft_putstr_fd("Error\nLibrary initialization mlx.\n", 1);
		return (-1);
	}
	mlx_get_screen_size(all.vars.mlx, &real_size_x, &real_size_y);
	if ((file.R_x > real_size_x || file.R_y > real_size_y) && all.file.check_save_image != 1)
	{
		file.R_x = real_size_x;
		file.R_y = real_size_y;
	}
	/*------------map---------------*/
	all.map.img = mlx_new_image(all.vars.mlx, 550, 250);
	//all.map.img = mlx_new_image(all.vars.mlx, all.map_mass.max_y * SIZE_MAP + 1, all.map_mass.max_x * SIZE_MAP + 1);
	all.map.addr = mlx_get_data_addr(all.map.img,
	&all.map.bits_per_pixel, &all.map.line_length, &all.map.endian);
	all.pl.img = mlx_new_image(all.vars.mlx, SIZE_PLAYER, SIZE_PLAYER);
	all.pl.addr = mlx_get_data_addr(all.pl.img,
			&all.pl.bits_per_pixel, &all.pl.line_length, &all.pl.endian);
	all.key.map = 0;
	/*------------mapend------------*/
	if (init_all(&all, file) == -1)
		return (-1);
	create_map(all.file.map, &all);
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
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 01:42:58 by dwanetta          #+#    #+#             */
/*   Updated: 2021/04/19 01:43:33 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_floor_and_ceilling(t_all *all, int ceilling, int floor)
{
	if (ceilling != 0)
	{
		while (ceilling >= 0)
		{
			my_mlx_pixel_put(&all->data, all->visual.width, ceilling,
				create_trgb(0, all->file.C[0], all->file.C[1], all->file.C[2]));
			ceilling--;
		}
	}
	if (floor != all->file.R_y)
	{
		while (floor < all->file.R_y)
		{
			my_mlx_pixel_put(&all->data, all->visual.width, floor,
				create_trgb(0, all->file.F[0], all->file.F[1], all->file.F[2]));
			floor++;
		}
	}
}

void	put_pix_texture(t_all *all, t_maping_texture *texture)
{
	if (texture->y_mass + SIZE_CHUNK - SIZE_PLAYER == (int)round(texture->y)
		&& (all->file.map[(texture->y_mass / SIZE_CHUNK) + 1]
			[texture->x_mass / SIZE_CHUNK] != '1'))
		my_mlx_pixel_put(&all->data, all->visual.width, texture->y_tmp,
			(int)get_color_image(&all->NO_texture,
				(int)all->NO_texture.color_x, (int)all->NO_texture.color_y));
	else if ((texture->y_mass == (int)round(texture->y))
		&& (all->file.map[(texture->y_mass / SIZE_CHUNK) - 1]
			[texture->x_mass / SIZE_CHUNK] != '1'))
		my_mlx_pixel_put(&all->data, all->visual.width, texture->y_tmp,
			(int)get_color_image(&all->SO_texture,
				(int)all->SO_texture.color_x, (int)all->SO_texture.color_y));
	else if ((texture->x_mass + SIZE_CHUNK - SIZE_PLAYER
			<= (int)round(texture->x))
		&& (all->file.map[texture->y_mass / SIZE_CHUNK]
			[(texture->x_mass / SIZE_CHUNK) + 1] != '1'))
		my_mlx_pixel_put(&all->data, all->visual.width, texture->y_tmp,
			(int)get_color_image(&all->EA_texture,
				(int)all->EA_texture.color_x, (int)all->EA_texture.color_y));
	else if ((texture->x_mass == (int)round(texture->x))
		&& (all->file.map[texture->y_mass / SIZE_CHUNK]
			[(texture->x_mass / SIZE_CHUNK) - 1] != '1'))
		my_mlx_pixel_put(&all->data, all->visual.width, texture->y_tmp,
			(int)get_color_image(&all->WE_texture,
				(int)all->WE_texture.color_x, (int)all->WE_texture.color_y));
}

void	put_texture_help(t_all *all, t_maping_texture *texture)
{
	if (SIZE_CHUNK > all->NO_texture.width)
		all->NO_texture.color_x = (int)(((int)texture->x % SIZE_CHUNK)
				/ (SIZE_CHUNK / all->NO_texture.width));
	else
		all->NO_texture.color_x = (int)(((int)texture->x % SIZE_CHUNK)
				* (all->NO_texture.width / SIZE_CHUNK));
	if (SIZE_CHUNK > all->SO_texture.width)
		all->SO_texture.color_x = (int)(((int)texture->x % SIZE_CHUNK)
				/ (SIZE_CHUNK / all->SO_texture.width));
	else
		all->SO_texture.color_x = (int)(((int)texture->x % SIZE_CHUNK)
				* (all->SO_texture.width / SIZE_CHUNK));
	if (SIZE_CHUNK > all->EA_texture.width)
		all->EA_texture.color_x = (int)(((int)texture->y % SIZE_CHUNK)
				/ (SIZE_CHUNK / all->EA_texture.width));
	else
		all->EA_texture.color_x = (int)(((int)texture->y % SIZE_CHUNK)
				* (all->EA_texture.width / SIZE_CHUNK));
	if (SIZE_CHUNK > all->WE_texture.width)
		all->WE_texture.color_x = (int)(((int)texture->y % SIZE_CHUNK)
				/ (SIZE_CHUNK / all->WE_texture.width));
	else
		all->WE_texture.color_x = (int)(((int)texture->y % SIZE_CHUNK)
				* (all->WE_texture.width / SIZE_CHUNK));
}

void	put_texture(t_all *all, t_maping_texture *texture, int h, int h_real)
{
	int	k;
	int	i;

	i = 0;
	put_texture_help(all, texture);
	print_floor_and_ceilling(all, 0, texture->y_tmp);
	while (texture->y_tmp >= (all->file.R_y / 2) - (h / 2)
		&& texture->y_tmp >= 0 )
	{
		k = ((h + h_real) >> 1) - i;
		all->NO_texture.color_y = (int)((all->NO_texture.height - 1)
				* k / h_real);
		all->SO_texture.color_y = (int)((all->SO_texture.height - 1)
				* k / h_real);
		all->EA_texture.color_y = (int)((all->EA_texture.height - 1)
				* k / h_real);
		all->WE_texture.color_y = (int)((all->WE_texture.height - 1)
				* k / h_real);
		put_pix_texture(all, texture);
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
	l *= cos(fabs(all->visual.ugl - (all->angle.alpha * (PI / 180))));
	h = (int)round((SIZE_CHUNK / l) * all->visual.distC);
	h_real = h;
	if (h > all->file.R_y)
		h = all->file.R_y;
	texture.y_tmp = (all->file.R_y / 2) + (h / 2) - 1;
	texture.x_mass = (int)(round(x) / SIZE_CHUNK) *SIZE_CHUNK;
	texture.y_mass = (int)(round(y) / SIZE_CHUNK) *SIZE_CHUNK;
	texture.x = x;
	texture.y = y;
	put_texture(all, &texture, h, h_real);
}

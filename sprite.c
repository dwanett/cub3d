/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 01:37:53 by dwanetta          #+#    #+#             */
/*   Updated: 2021/04/19 01:40:07 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_curr_sprite(t_all *all)
{
	int	j;
	int	i;

	i = -1;
	while (i < all->sprite->size - 1)
	{
		i++;
		if (all->sprite->start + i < 0
			|| all->sprite->start + i >= all->file.R_x
			|| all->visual.rey_len[all->sprite->start + i] < all->sprite->dist)
			continue ;
		j = -1;
		while (j < all->sprite->size - 1)
		{
			j++;
			if (all->sprite->y_start + j < 0
				|| all->sprite->y_start + j >= all->file.R_y)
				continue ;
			my_mlx_pixel_put(&all->data, (int)(all->sprite->start + i),
				(int)(all->sprite->y_start + j),
				(int)get_color_image(&all->S_texture,
					(int)(i * all->S_texture.width / all->sprite->size),
					(int)(j * all->S_texture.height / all->sprite->size)));
		}
	}
}

void	print_sprite(t_all *all)
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

void	init_sprite_help(t_all *all, double step)
{
	double	teta;

	teta = atan2(all->sprite->y - all->player.y,
			all->sprite->x - all->player.x);
	all->sprite->dist = sqrt(pow(all->sprite->x - all->player.x, 2)
			+ pow(all->sprite->y - all->player.y, 2));
	while (teta - (all->angle.alpha * (PI / 180)) > PI)
		teta -= 2 * PI;
	while (teta - (all->angle.alpha * (PI / 180)) < -PI)
		teta += 2 * PI;
	all->sprite->size = (int)round(((SIZE_CHUNK / SCALE)
				/ all->sprite->dist) * all->visual.distC);
	all->sprite->start = (int)((all->file.R_x - 1) / 2.0
			+ (teta - (all->angle.alpha * (PI / 180)))
			/ step - all->sprite->size / 2.0);
	all->sprite->y_start = (all->file.R_y / 2)
		+ (all->sprite->size / SIZE_CHUNK);
	all->sprite = all->sprite->next;
}

void	init_sprite(t_all *all, double step)
{
	t_sprite	*tmp;

	tmp = all->sprite;
	while (all->sprite != NULL)
		init_sprite_help(all, step);
	all->sprite = tmp;
	all->sprite = sort_list(all->sprite);
	print_sprite(all);
	all->visual.sprite_yes = 0;
}

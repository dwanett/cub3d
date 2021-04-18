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

int check(double n1, double n2)
{
	if (n1 > n2)
		return (0);
	else
		return (1);
}

t_sprite *sort_list(t_sprite *head)
{
	t_sprite *q;
	t_sprite *out;
	t_sprite *p;
	t_sprite *pr;

	out = NULL;
	while (head != NULL)
	{
		q = head;
		head = head->next;
		p = out, pr = NULL;
		while (p != NULL && check(q->dist, p->dist) > 0)
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

void print_curr_sprite(t_all *all)
{
	int j;
	int i;

	i = -1;
	while (i < all->sprite->size)
	{
		i++;
		if (all->sprite->start + i < 0 ||
			all->sprite->start + i >= all->file.R_x ||
			all->visual.rey_len[all->sprite->start + i] < all->sprite->dist)
			continue;
		j = -1;
		while (j < all->sprite->size - 1)
		{
			j++;
			if (all->sprite->y_start + j < 0 ||
				all->sprite->y_start + j >= all->file.R_y)
				continue;
			my_mlx_pixel_put(&all->data, (int)(all->sprite->start + i),
			(int)(all->sprite->y_start + j), (int)get_color_image(&all->S_texture,
			(int)(i * all->S_texture.width / all->sprite->size),
			(int)(j * all->S_texture.height / all->sprite->size)));
		}
	}
}

void print_sprite(t_all *all)
{
	t_sprite *tmp;

	tmp = all->sprite;
	while (all->sprite != NULL)
	{
		print_curr_sprite(all);
		all->sprite = all->sprite->next;
	}
	all->sprite = tmp;
}

void init_sprite(t_all *all, double step)
{
	t_sprite *tmp;
	double teta;

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
										all->sprite->dist) *
									   all->visual.distC);
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
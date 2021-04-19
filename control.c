/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 21:43:50 by dwanetta          #+#    #+#             */
/*   Updated: 2021/03/19 21:44:03 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	walking(t_all *all, double x, double y, int key)
{
	walking_help(all, &x, &y, key);
	if (chek_position(all, &x, &y)
		&& all->key.keycode != ARROW_LEFT && all->key.keycode != ARROW_RIGHT)
	{
		all->player.x = x;
		all->player.y = y;
	}
	if (chek_position(all, &x, &all->player.y)
		&& all->key.keycode != ARROW_LEFT && all->key.keycode != ARROW_RIGHT)
		all->player.x = x;
	if (chek_position(all, &all->player.x, &y)
		&& all->key.keycode != ARROW_LEFT && all->key.keycode != ARROW_RIGHT)
		all->player.y = y;
}

void	move(t_all *all)
{
	walking(all, all->player.x, all->player.y, all->key.keycode);
	if (all->key.keycode == ARROW_LEFT)
		all->angle.alpha -= SPEED_ANGLE;
	if (all->key.keycode == ARROW_RIGHT)
		all->angle.alpha += SPEED_ANGLE;
	if (all->angle.alpha >= 360)
		all->angle.alpha = 0;
	else if (all->angle.alpha <= 0)
		all->angle.alpha = 360;
}

int	ft_key_hook(int keycode, t_all *all)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(all->vars.mlx, all->vars.win);
		free(all->visual.rey_len);
		if (all->sprite != NULL)
			free_sprite(all);
		exit(-1);
	}
	if (keycode == W || keycode == S || keycode == A
		|| keycode == D || keycode == M
		|| keycode == ARROW_LEFT || keycode == ARROW_RIGHT)
		all->key.keycode = keycode;
	return (0);
}

int	ft_close_exit(t_all *all)
{
	free(all->visual.rey_len);
	if (all->sprite != NULL)
		free_sprite(all);
	exit(0);
	return (0);
}

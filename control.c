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

int	chek_position(t_all *all, double x, double y)
{
	if (!((all->file.map[(int) (round(y) / SIZE_CHUNK)]
		   [(int) (round(x) / SIZE_CHUNK)] == '1')
		  || (all->file.map[(int) (round(y + SIZE_PLAYER - 1) / SIZE_CHUNK)]
			  [(int) (round(x) / SIZE_CHUNK)] == '1')
		  || (all->file.map[(int) (round(y) / SIZE_CHUNK)]
			  [(int) (round(x + SIZE_PLAYER - 1) / SIZE_CHUNK)] == '1')
		  || (all->file.map[(int) (round(y + SIZE_PLAYER - 1) / SIZE_CHUNK)]
			  [(int) (round(x + SIZE_PLAYER - 1) / SIZE_CHUNK)] == '1')))
		return (1);
	return (0);
}

void walking(t_all *all, double x, double y, int key)
{
	if (key == W)
	{
		x += SPEED * cos((all->angle.alpha * PI / 180));
		y += SPEED * sin((all->angle.alpha * PI / 180));
	}
	if (key == A)
	{
		x -= SPEED * cos((all->angle.alpha * PI / 180) + PI / 2);
		y -= SPEED * sin((all->angle.alpha * PI / 180) + PI / 2);
	}
	if (key == S)
	{
		x -= SPEED * cos((all->angle.alpha * PI / 180));
		y -= SPEED * sin((all->angle.alpha * PI / 180));
	}
	if (key == D)
	{
		x += SPEED * cos((all->angle.alpha * PI / 180) + PI / 2);
		y += SPEED * sin((all->angle.alpha * PI / 180) + PI / 2);
	}
	if (chek_position(all, x, y))
	{
		all->player.x = x;
		all->player.y = y;
	}
}

void move(t_all *all)
{
	walking(all, all->player.x, all->player.y, all->key.keycode);
	if (all->key.keycode == ARROW_LEFT)
		all->angle.alpha -= SPEED * 2;
	if (all->key.keycode == ARROW_RIGHT)
		all->angle.alpha += SPEED * 2;
	if (all->angle.alpha >= 360)
		all->angle.alpha = 0;
	else if (all->angle.alpha <= 0)
		all->angle.alpha = 360;
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
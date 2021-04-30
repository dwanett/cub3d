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

int chek_position(t_all *all, double x1, double y1, double *x2, double *y2)
{
	int deltaX;
	int deltaY;
	int length;
	double dX;
	double dY;

	deltaX = abs((int)(round(x1) - round(*x2)));
	deltaY = abs((int)(round(y1) - round(*y2)));
	length = MAX(deltaX, deltaY);
	if (length == 0)
	{
		*x2 = x1;
		*y2 = y1;
		return (0);
	}
	dX = (*x2 - x1) / length;
	dY = (*y2 - y1) / length;
	length++;
	while (length--)
	{
		x1 += dX;
		y1 += dY;
		if (all->file.map[(int)(round(y1) / SIZE_CHUNK)][(int)(round(x1) / SIZE_CHUNK)] == '1')
			return (0) ;
		*x2 = x1;
		*y2 = y1;
	}
	return (1);
}

void walking(t_all *all, double x, double y, int key)
{
	if (key == W)
	{
		x += SPEED_MOVE * cos((all->angle.alpha * PI / 180));
		y += SPEED_MOVE * sin((all->angle.alpha * PI / 180));
	}
	if (key == A)
	{
		x -= SPEED_MOVE * cos((all->angle.alpha * PI / 180) + PI / 2);
		y -= SPEED_MOVE * sin((all->angle.alpha * PI / 180) + PI / 2);
	}
	if (key == S)
	{
		x -= SPEED_MOVE * cos((all->angle.alpha * PI / 180));
		y -= SPEED_MOVE * sin((all->angle.alpha * PI / 180));
	}
	if (key == D)
	{
		x += SPEED_MOVE * cos((all->angle.alpha * PI / 180) + PI / 2);
		y += SPEED_MOVE * sin((all->angle.alpha * PI / 180) + PI / 2);
	}
	if (chek_position(all, all->player.x, all->player.y, &x, &y) && all->key.keycode != ARROW_LEFT && all->key.keycode != ARROW_RIGHT)
	{
		all->player.x = x;
		all->player.y = y;
	}
	if (chek_position(all, all->player.x, all->player.y, &x, &all->player.y) && all->key.keycode != ARROW_LEFT && all->key.keycode != ARROW_RIGHT)
		all->player.x = x;
	if (chek_position(all, all->player.x, all->player.y, &all->player.x, &y) && all->key.keycode != ARROW_LEFT && all->key.keycode != ARROW_RIGHT)
		all->player.y = y;
}

void move(t_all *all)
{
	walking(all, all->player.x, all->player.y, all->key.keycode);
	//------------map---------------
	if (all->key.keycode == M && all->key.map != 1)
		all->key.map = 1;
	else if (all->key.keycode == M && all->key.map != 0)
		all->key.map = 0;
	//------------mapend-------------
	if (all->key.keycode == ARROW_LEFT)
		all->angle.alpha -= SPEED_ANGLE;
	if (all->key.keycode == ARROW_RIGHT)
		all->angle.alpha += SPEED_ANGLE;
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
		free(all->visual.rey_len);
		if (all->sprite != NULL)
			free_sprite(all);
		exit(-1);
	}
	if (keycode == W || keycode == S || keycode == A || keycode == D || keycode == M
		|| keycode == ARROW_LEFT || keycode == ARROW_RIGHT)
		all->key.keycode = keycode;
	return (0);
}

int ft_key_stop(int keycode, t_all *all)
{
	if (keycode == W || keycode == S || keycode == A || keycode == D || keycode == M
		|| keycode == ARROW_LEFT || keycode == ARROW_RIGHT)
		all->key.keycode = -1;
	return (0);
}

int ft_close_exit(t_all *all)
{
	free(all->visual.rey_len);
	if (all->sprite != NULL)
		free_sprite(all);
	exit(-1);
}

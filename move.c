/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 21:43:50 by dwanetta          #+#    #+#             */
/*   Updated: 2021/03/19 21:44:03 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	chek_position_help(double x1, double y1, double *x2, double *y2)
{
	int	length;

	if (abs((int)(round(x1) - round(*x2))) > abs((int)(round(y1) - round(*y2))))
		length = abs((int)(round(x1) - round(*x2)));
	else
		length = abs((int)(round(y1) - round(*y2)));
	return (length);
}

int	chek_position(t_all *all, double *x2, double *y2)
{
	double	x1;
	double	y1;
	int		length;
	double	dX;
	double	dY;

	x1 = all->player.x;
	y1 = all->player.y;
	length = chek_position_help(x1, y1, x2, y2);
	if (length == 0)
		return (0);
	dX = (*x2 - x1) / length;
	dY = (*y2 - y1) / length;
	length++;
	while (length--)
	{
		x1 += dX;
		y1 += dY;
		if (all->file.map[(int)(round(y1) / SIZE_CHUNK)]
			[(int)(round(x1) / SIZE_CHUNK)] == '1')
			return (0);
		*x2 = x1;
		*y2 = y1;
	}
	return (1);
}

void	walking_help(t_all *all, double *x, double *y, int key)
{
	if (key == W)
	{
		*x += SPEED_MOVE * cos((all->angle.alpha * PI / 180));
		*y += SPEED_MOVE * sin((all->angle.alpha * PI / 180));
	}
	if (key == A)
	{
		*x -= SPEED_MOVE * cos((all->angle.alpha * PI / 180) + PI / 2);
		*y -= SPEED_MOVE * sin((all->angle.alpha * PI / 180) + PI / 2);
	}
	if (key == S)
	{
		*x -= SPEED_MOVE * cos((all->angle.alpha * PI / 180));
		*y -= SPEED_MOVE * sin((all->angle.alpha * PI / 180));
	}
	if (key == D)
	{
		*x += SPEED_MOVE * cos((all->angle.alpha * PI / 180) + PI / 2);
		*y += SPEED_MOVE * sin((all->angle.alpha * PI / 180) + PI / 2);
	}
}

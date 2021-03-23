/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 21:14:36 by dwanetta          #+#    #+#             */
/*   Updated: 2021/03/23 21:14:36 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void print_player(t_all *all)
{
	int	tmp_y;
	int	tmp_x;

	tmp_y = (int)(all->player.y / SIZE_CHUNK * SIZE_MAP);
	tmp_x = (int)(all->player.x / SIZE_CHUNK * SIZE_MAP);
	print_kodred(all, SIZE_PLAYER, 0x00FF0000, tmp_x, tmp_y);
}

void color_map(char symbol, int *color)
{
	if (symbol == ' ')
		*color = 0x00000000;
	if (symbol == '1')
		*color = 0x000FF000;
	if (symbol == '0')
		*color = 0x000FFFF0;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 22:46:05 by dwanetta          #+#    #+#             */
/*   Updated: 2021/04/19 13:26:25 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			free_sprite(t_all *all)
{
	t_sprite	*tmp;

	while (all->sprite != NULL)
	{
		tmp = all->sprite->next;
		free(all->sprite);
		all->sprite = tmp;
	}
}

void			full_free_file(t_file *file)
{
	int	i;

	i = 0;
	free(file->NO_texture);
	free(file->SO_texture);
	free(file->WE_texture);
	free(file->EA_texture);
	free(file->S_texture);
	while (file->map[i] != NULL)
		free(file->map[i++]);
	free(file->map);
}

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	if ((unsigned int)color == 0xFF000000)
		return ;
	*(unsigned int *)dst = color;
}

int				create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

unsigned int	get_color_image(t_texture *texture, int x, int y)
{
	char	*dst;

	dst = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
/*	if (*(unsigned int *)dst == 0)
		return (0xFF000000);*/
	return (*(unsigned int *)dst);
}

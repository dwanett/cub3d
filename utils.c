/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 22:46:05 by dwanetta          #+#    #+#             */
/*   Updated: 2021/03/22 22:46:05 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	full_free_file(t_file *file)
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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_color_image(t_texture *texture, int x, int y)
{
	char *dst;

	dst = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}


int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}
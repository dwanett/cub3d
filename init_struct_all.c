/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_all.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 01:05:29 by dwanetta          #+#    #+#             */
/*   Updated: 2021/04/19 01:19:40 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_all_help_2(t_all *all)
{
	all->NO_texture.addr = mlx_get_data_addr(all->NO_texture.img,
	&all->NO_texture.bits_per_pixel, &all->NO_texture.line_length,
	&all->NO_texture.endian);
	all->SO_texture.addr = mlx_get_data_addr(all->SO_texture.img,
	&all->SO_texture.bits_per_pixel, &all->SO_texture.line_length,
	&all->SO_texture.endian);
	all->WE_texture.addr = mlx_get_data_addr(all->WE_texture.img,
	&all->WE_texture.bits_per_pixel, &all->WE_texture.line_length,
	&all->WE_texture.endian);
	all->EA_texture.addr = mlx_get_data_addr(all->EA_texture.img,
	&all->EA_texture.bits_per_pixel, &all->EA_texture.line_length,
	&all->EA_texture.endian);
	all->S_texture.addr = mlx_get_data_addr(all->S_texture.img,
	&all->S_texture.bits_per_pixel, &all->S_texture.line_length,
	&all->S_texture.endian);
}

int		init_all_help_1(t_all *all, t_file file)
{
	all->sprite = NULL;
	all->visual.sprite_yes = 0;
	all->visual.count_sprite = 0;
	all->player.x = 0;
	all->player.y = 0;
	all->map_mass.x = 0;
	all->map_mass.y = 0;
	all->map_mass.max_x = 0;
	all->map_mass.max_y = 0;
	all->pix_for_map.x = 0;
	all->pix_for_map.y = 0;
	all->vars.win = mlx_new_window(all->vars.mlx, file.R_x, file.R_y, "cub3d");
	all->data.img = mlx_new_image(all->vars.mlx, file.R_x, file.R_y);
	all->data.addr = mlx_get_data_addr(all->data.img,
	&all->data.bits_per_pixel, &all->data.line_length, &all->data.endian);
	all->file = file;
	all->visual.rey_len = (double *)malloc(sizeof(double) * all->file.R_x);
	if (all->visual.rey_len == NULL)
		return (-1);
	return (0);
}

int		init_all(t_all *all, t_file file)
{
	if (init_all_help_1(all, file) == -1)
		return (-1);
	all->NO_texture.img = mlx_xpm_file_to_image(all->vars.mlx,
	all->file.NO_texture, &all->NO_texture.width, &all->NO_texture.height);
	all->SO_texture.img = mlx_xpm_file_to_image(all->vars.mlx,
	all->file.SO_texture, &all->SO_texture.width, &all->SO_texture.height);
	all->WE_texture.img = mlx_xpm_file_to_image(all->vars.mlx,
	all->file.WE_texture, &all->WE_texture.width, &all->WE_texture.height);
	all->EA_texture.img = mlx_xpm_file_to_image(all->vars.mlx,
	all->file.EA_texture, &all->EA_texture.width, &all->EA_texture.height);
	all->S_texture.img = mlx_xpm_file_to_image(all->vars.mlx,
	all->file.S_texture, &all->S_texture.width, &all->S_texture.height);
	if (all->NO_texture.img == NULL || all->SO_texture.img == NULL ||
		all->WE_texture.img == NULL || all->EA_texture.img == NULL ||
		all->S_texture.img == NULL)
	{
		print_error_img(all);
		return (-1);
	}
	init_all_help_2(all);
	return (0);
}
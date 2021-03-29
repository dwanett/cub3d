/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 12:42:25 by dwanetta          #+#    #+#             */
/*   Updated: 2021/03/24 12:45:03 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error_img(t_all *all)
{
	if (all->NO_texture.img == NULL)
		ft_putstr_fd("Error\nСould not read the wall texture file NO\n", 1);
	if (all->SO_texture.img == NULL)
		ft_putstr_fd("Error\nСould not read the wall texture file SO\n", 1);
	if (all->WE_texture.img == NULL)
		ft_putstr_fd("Error\nСould not read the wall texture file WE\n", 1);
	if (all->EA_texture.img == NULL)
		ft_putstr_fd("Error\nСould not read the wall texture file EA\n", 1);
	if (all->S_texture.img == NULL)
		ft_putstr_fd("Error\nСould not read sprite texture file S\n", 1);
}

void	angel_palyer(t_all *all, int *color, char **map)
{
	if ((map[all->map_mass.x][all->map_mass.y] == 'N' ||
		 map[all->map_mass.x][all->map_mass.y] == 'S' ||
		 map[all->map_mass.x][all->map_mass.y] == 'E' ||
		 map[all->map_mass.x][all->map_mass.y] == 'W') &&
		all->player.x == 0)
	{
		if (map[all->map_mass.x][all->map_mass.y] == 'S')
			all->angle.alpha = 90;
		if (map[all->map_mass.x][all->map_mass.y] == 'W')
			all->angle.alpha = 180;
		if (map[all->map_mass.x][all->map_mass.y] == 'N')
			all->angle.alpha = 270;
		if (map[all->map_mass.x][all->map_mass.y] == 'E')
			all->angle.alpha = 0;
		all->player.x = all->map_mass.y * SIZE_CHUNK;
		all->player.y = all->map_mass.x * SIZE_CHUNK;
		map[all->map_mass.x][all->map_mass.y] = '0';
		*color = 0x000FFFF0;
	}
}

void	save_max_map_value(t_all *all, int x, int y)
{
	if (x > all->map_mass.max_x)
		all->map_mass.max_x = x;
	if (y > all->map_mass.max_y)
		all->map_mass.max_y = y;
}

void	create_map(char **map, t_all *all)
{
	int	color;

	color = 0x00000000;
	while (map[all->map_mass.x] != NULL)
	{
		all->map_mass.y = 0;
		while (map[all->map_mass.x][all->map_mass.y] != '\0')
		{
			/*------------map---------------*/
			color_map(map[all->map_mass.x][all->map_mass.y], &color);
			/*------------mapend-------------*/
			angel_palyer(all, &color, map);
			/*------------map---------------*/
			print_kodred(all, SIZE_MAP, color,
						 all->pix_for_map.x, all->pix_for_map.y);
			all->pix_for_map.x += SIZE_MAP;
			/*------------mapend-------------*/
			all->map_mass.y++;
		}
		/*------------map---------------*/
		all->pix_for_map.x = 0;
		all->pix_for_map.y += SIZE_MAP;
		/*------------mapend-------------*/
		all->map_mass.x++;
		save_max_map_value(all, all->map_mass.x, all->map_mass.y);
	}
}

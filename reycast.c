/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 16:50:18 by dwanetta          #+#    #+#             */
/*   Updated: 2021/04/19 16:51:18 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	reycast_help_verti(t_all *all, t_reycast *verti, double cos_a)
{
	double	tmp_cor;

	tmp_cor = all->player.x;
	while (1)
	{
		verti->dist_x = floor(tmp_cor / SIZE_CHUNK)
			* SIZE_CHUNK + (verti->raz * SIZE_CHUNK);
		if (cos_a < 0)
			verti->dist_x += SIZE_CHUNK - SIZE_PLAYER;
		verti->dist = fabs(verti->dist_x - tmp_cor) / cos_a;
		verti->gip += (verti->dist * sin(all->visual.ugl) * (verti->raz));
		if (verti->gip < 0 || verti->dist_x < 0
			|| (verti->gip / SIZE_CHUNK >= all->map_mass.max_x))
			break ;
		if (all->file.map[(int)(floor(verti->gip) / SIZE_CHUNK)]
			[(int)(floor(verti->dist_x) / SIZE_CHUNK)] == '1')
			break ;
		if (all->file.map[(int)(floor(verti->gip) / SIZE_CHUNK)]
			[(int)(floor(verti->dist_x) / SIZE_CHUNK)] == '2')
			all->visual.sprite_yes = 1;
		tmp_cor = verti->dist_x;
	}
}

void	reycast_help_horiz(t_all *all, t_reycast *horiz, double sin_a)
{
	double	tmp_cor;

	tmp_cor = all->player.y;
	while (1)
	{
		horiz->dist_y = floor((tmp_cor / SIZE_CHUNK))
			* SIZE_CHUNK + (horiz->raz * SIZE_CHUNK);
		if (sin_a < 0)
			horiz->dist_y += SIZE_CHUNK - SIZE_PLAYER;
		horiz->dist = fabs(horiz->dist_y - tmp_cor) / sin_a;
		horiz->gip += (horiz->dist * cos(all->visual.ugl) * (horiz->raz));
		if (horiz->dist_y < 0 || horiz->gip < 0
			|| (horiz->gip / SIZE_CHUNK >= all->map_mass.max_y)
			|| (horiz->dist_y / SIZE_CHUNK >= all->map_mass.max_x))
			break ;
		if (all->file.map[(int)(floor(horiz->dist_y) / SIZE_CHUNK)]
			[(int)(floor(horiz->gip) / SIZE_CHUNK)] == '1')
			break ;
		if (all->file.map[(int)(floor(horiz->dist_y) / SIZE_CHUNK)]
			[(int)(floor(horiz->gip) / SIZE_CHUNK)] == '2')
			all->visual.sprite_yes = 1;
		tmp_cor = horiz->dist_y;
	}
}

void	reycast_help_init(t_all *all, t_reycast *horiz, t_reycast *verti)
{
	double		cos_a;
	double		sin_a;

	cos_a = cos(all->visual.ugl);
	sin_a = sin(all->visual.ugl);
	verti->gip = all->player.y + SIZE_PLAYER;
	horiz->gip = all->player.x + SIZE_PLAYER;
	horiz->raz = -1;
	verti->raz = -1;
	if (cos_a >= 0)
	{
		verti->gip = all->player.y;
		horiz->gip = all->player.x;
		verti->raz = 1;
	}
	if (sin_a >= 0)
	{
		horiz->gip = all->player.x;
		verti->gip = all->player.y;
		horiz->raz = 1;
	}
	reycast_help_verti(all, verti, cos_a);
	reycast_help_horiz(all, horiz, sin_a);
}

void	reycast(t_all *all)
{
	t_reycast	horiz;
	t_reycast	verti;
	double		step;

	all->visual.ugl = (all->angle.alpha - (int)FOV2) * (PI / 180);
	all->visual.distC = (all->file.R_x / 2.0) / tan((int)FOV2 * (PI / 180));
	all->visual.width = 0;
	step = (FOV * (PI / 180)) / (all->file.R_x - 1);
	while (all->visual.ugl <= ((all->angle.alpha + (int)FOV2) * (PI / 180)))
	{
		reycast_help_init(all, &horiz, &verti);
		horiz.l = sqrt(pow((all->player.x - horiz.gip), 2)
				+ pow((all->player.y - horiz.dist_y), 2));
		verti.l = sqrt(pow((all->player.x - verti.dist_x), 2)
				+ pow((all->player.y - verti.gip), 2));
		if (fabs(horiz.l) < fabs(verti.l))
			print3d(all, horiz.gip, horiz.dist_y, horiz.l);
		else
			print3d(all, verti.dist_x, verti.gip, verti.l);
		all->visual.ugl += step;
		all->visual.width++;
	}
	if (all->visual.sprite_yes == 1)
		init_sprite(all, step);
}

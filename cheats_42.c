/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheats_42.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 21:33:05 by dwanetta          #+#    #+#             */
/*   Updated: 2021/03/23 21:50:43 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "cub3d.h"

int myFPS(t_all *all)
{
	clock_t current_ticks, delta_ticks;
	clock_t fps = 0;
	current_ticks = clock();
	render_next_frame(all);
	delta_ticks = clock() - current_ticks;
	if (delta_ticks > 0)
		fps = CLOCKS_PER_SEC / delta_ticks;
	mlx_string_put(all->vars.mlx, all->vars.win, 5,
	11, 0x00FF0000, ft_itoa(fps));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:33:24 by dwanetta          #+#    #+#             */
/*   Updated: 2021/03/24 13:27:08 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			render_next_frame(t_all *all)
{
	print_player(all);/*------------map---------------*/
	reycast(all);
	if (all->file.check_save_image == 1)
	{
		create_bmp(all);
		ft_close_exit(all);
	}
	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->data.img, 0, 0);
	/*------------map---------------*/
	if (all->key.map == 1)
	{
		mlx_put_image_to_window(all->vars.mlx, all->vars.win,
				all->map.img, 0, 0);
		mlx_put_image_to_window(all->vars.mlx, all->vars.win,
		all->pl.img, (int)(all->player.x / SIZE_CHUNK * SIZE_MAP),
		(int)(all->player.y / SIZE_CHUNK * SIZE_MAP));
	}
	/*------------mapend------------*/
	if (all->key.keycode >= 0)
	{
		mlx_destroy_image(all->vars.mlx, all->data.img);
		all->data.img = mlx_new_image(all->vars.mlx,
		all->file.R_x, all->file.R_y);
		all->data.addr = mlx_get_data_addr(all->data.img,
		&all->data.bits_per_pixel, &all->data.line_length,
		&all->data.endian);
		/*------------map---------------*/
		mlx_destroy_image(all->vars.mlx, all->pl.img);
		all->pl.img = mlx_new_image(all->vars.mlx,
				SIZE_PLAYER, SIZE_PLAYER);
		all->pl.addr = mlx_get_data_addr(all->pl.img,
				&all->pl.bits_per_pixel, &all->pl.line_length,
				&all->pl.endian);
		/*------------mapend------------*/
		move(all);
	}
	all->key.keycode = -1;
	return (0);
}

int			ft_window(t_file file)
{
	t_all	all;
	int 	real_size_x;
	int 	real_size_y;

	if ((all.vars.mlx = mlx_init()) == NULL)
	{
		ft_putstr_fd("Error\nLibrary initialization mlx.\n", 1);
		return (-1);
	}
# ifndef __APPLE__
	mlx_get_screen_size(all.vars.mlx, &real_size_x, &real_size_y);
#else
	mlx_get_screen_size(&real_size_x, &real_size_y);
#endif
	if (file.check_save_image != 1 && (file.R_x > real_size_x || file.R_y > real_size_y))
	{
		file.R_x = real_size_x;
		file.R_y = real_size_y;
	}
	/*------------map---------------*/
	all.map.img = mlx_new_image(all.vars.mlx, 550, 250);
	//all.map.img = mlx_new_image(all.vars.mlx, all.map_mass.max_y * SIZE_MAP + 1, all.map_mass.max_x * SIZE_MAP + 1);
	all.map.addr = mlx_get_data_addr(all.map.img,
	&all.map.bits_per_pixel, &all.map.line_length, &all.map.endian);
	all.pl.img = mlx_new_image(all.vars.mlx, SIZE_PLAYER, SIZE_PLAYER);
	all.pl.addr = mlx_get_data_addr(all.pl.img,
			&all.pl.bits_per_pixel, &all.pl.line_length, &all.pl.endian);
	all.key.map = 0;
	/*------------mapend------------*/
	if (init_all(&all, file) == -1)
		return (-1);
	create_map(all.file.map, &all);
	mlx_loop_hook(all.vars.mlx, myFPS, &all);
	//mlx_loop_hook(all.vars.mlx, render_next_frame, &all);
	mlx_hook(all.vars.win, 2, 1L << 0, ft_key_hook, &all);
	mlx_hook(all.vars.win, CLOSE, 0, ft_close_exit, &all);
	mlx_loop(all.vars.mlx);
	return (0);
}

int			main(int argc, char *argv[])
{
	t_file	file;

	if (ft_open_file(argc, argv, &file) == -1)
		exit(-1);
	if (ft_check_init_file(&file) == -1)
		exit(-1);
	if (ft_window(file) == -1)
		exit(-1);
	full_free_file(&file);
	return (0);
}

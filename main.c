/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:33:24 by dwanetta          #+#    #+#             */
/*   Updated: 2021/02/22 18:02:34 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_linux/mlx.h"
//#include "mlx_mac/mlx.h"
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"
#include <math.h>

#include <stdio.h>
#include <fcntl.h>

#define X 940
#define Y 540
#define FOV 3.14 / 3

typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data;

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int main(void)
{
	void *mlx;
	void *mlx_win;
	t_data img;
	int x;
	int y;
	int fd;
	char *line;

	x = 0;
	y = 0;
	fd = open("main.c", O_RDONLY);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, X, Y, "Hello world!");
	img.img = mlx_new_image(mlx, X, Y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
	while (x != 50)
	{
		y = 0;
		while (y != 50)
		{
			my_mlx_pixel_put(&img, x, y, 0x00b3b3b3);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	//mlx_loop(mlx);
	while (get_next_line(fd, &line) != 0)
	{
		printf("%s\n", line);
		free(line);
	}
	printf("%s\n", line);
	free(line);
}

/*
int main(void)
{
	void *mlx;
	void *mlx_win;
	int x;
	int y;
	int k;

	x = 30;
	y = 30;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 960, 540, "Hello world!");
	mlx_pixel_put(mlx, mlx_win, 1, 1, 0x00ff0000);
	while (x != 100)
	{
		y = (149*x-50) / 99;
		mlx_pixel_put(mlx, mlx_win, x, y, 0x00ff0000);
		x++;
	}
	mlx_pixel_put(mlx, mlx_win, 100, 150, 0x00ff0000);
	mlx_loop(mlx);
}*/
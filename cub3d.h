/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 18:41:07 by dwanetta          #+#    #+#             */
/*   Updated: 2021/03/18 14:28:54 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifdef __APPLE__
#  include "mlx_mac/mlx.h"
#  define CLOSE 17
#  define ESC 53
#  define W 13
#  define S 1
#  define A 0
#  define D 2
#  define ARROW_LEFT 123
#  define ARROW_RIGHT 124
# else
#  include "mlx_linux/mlx.h"
#  define CLOSE 33
#  define ESC 65307
#  define W 119
#  define S 115
#  define A 97
#  define D 100
#  define M 109
#  define ARROW_LEFT 65361
#  define ARROW_RIGHT 65363
# endif
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <math.h>
# include <fcntl.h>
//-----------------
#include <stdio.h>
//-----------------
# define PI 3.14159265358979323846
# define SIZE_CHUNK 128
# define SIZE_MAP 16
# define SIZE_PLAYER 2
# define SPEED_MOVE 15
# define SPEED_ANGLE 3
# define FOV 60
# define MAX(x, y) x > y ? x: y

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
}				t_vars;

typedef struct	s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_file
{
	int			R_x;
	int			R_y;
	char		*NO_texture;
	char		*SO_texture;
	char		*WE_texture;
	char		*EA_texture;
	char		*S_texture;
	int			F[3];
	int			C[3];
	char		**map;
}				t_file;

typedef struct	s_key
{
	int			keycode;
	int			map;
}				t_key;

typedef struct	s_reycast
{
	int			height;
	int			width;
	double		distC;
	double		ugl;
}				t_reycast;

typedef struct	s_posi
{
	double		x;
	double		y;
}				t_posi;

typedef struct	s_mas
{
	int			x;
	int			y;
}				t_mas;

typedef struct	s_angle
{
	int			alpha;
}				t_angle;

typedef struct	s_all
{
	t_file		file;
	t_vars		vars;
	t_data		data;
	t_key		key;
	t_posi		player;
	t_mas		map_mass;
	t_mas		pix_for_map;
	t_angle		angle;
	t_reycast	visual;
	t_data		map;
}				t_all;

int				check_last_str_map(char **tmp_map);
void			ft_save_map(char *line, char **tmp_map, int *return_gnl);
int				help_check_map(char **map, int *flag_player, int *i, int *j);
int				check_map(char **map);
int				ft_check_init_file(t_file *file);
int				ft_init_file_int(char *line, int *i);
void			ft_init_file_char(char *line, t_file *file,
				char **tmp_map, int *return_gnl);
void			ft_init_file(char *line, t_file *file, char **tmp_map,
				int *return_gnl);
int				ft_pars(int fd, t_file *file);
int				ft_open_file(int argc, char *argv[], t_file *file);
void			move(t_all *all);
int				ft_key_hook(int keycode, t_all *all);
int				ft_close_exit();

#endif

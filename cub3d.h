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

# include "mlx_mac/mlx.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <math.h>
# include <fcntl.h>

# define CLOSE 17
# define ESC 53
# define W 13
# define S 1
# define A 0
# define D 2
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define PI 3.14159265358979323846
# define SIZE_CHUNK 512
# define SCALE 1.9
# define SIZE_PLAYER 2
# define SPEED_MOVE 200
# define SPEED_ANGLE 3
# define FOV 60
# define FOV2 30

typedef struct s_vars
{
	void			*mlx;
	void			*win;
}					t_vars;

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;

typedef struct s_texture
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
	double			color_x;
	double			color_y;
}					t_texture;

typedef struct s_maping_texture
{
	int				x_mass;
	int				y_mass;
	int				y_tmp;
	double			x;
	double			y;
}					t_maping_texture;

typedef struct s_sprite
{
	double			x;
	double			y;
	double			dist;
	int				size;
	int				start;
	int				y_start;
	struct s_sprite	*next;
}					t_sprite;

typedef struct s_file
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
	int			check_save_image;
}				t_file;

typedef struct s_key
{
	int			keycode;
}				t_key;

typedef struct s_reycast
{
	int			width;
	double		distC;
	double		ugl;
	int			color;
	int			raz;
	double		gip;
	double		dist;
	double		dist_x;
	double		dist_y;
	double		l;
	double		*rey_len;
	int			sprite_yes;
	int			count_sprite;
}				t_reycast;

typedef struct s_posi
{
	double		x;
	double		y;
}				t_posi;

typedef struct s_mas
{
	int			x;
	int			y;
	int			max_x;
	int			max_y;
}				t_mas;

typedef struct s_angle
{
	double		alpha;
}				t_angle;

typedef struct s_all
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
	t_texture	NO_texture;
	t_texture	SO_texture;
	t_texture	WE_texture;
	t_texture	EA_texture;
	t_texture	S_texture;
	t_sprite	*sprite;
}				t_all;

int				check_last_str_map(char **tmp_map, int *return_gnl);
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
int				ft_close_exit(t_all *all);
void			full_free_file(t_file *file);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
unsigned int	get_color_image(t_texture *texture, int x, int y);
int				create_trgb(int t, int r, int g, int b);
int				render_next_frame(t_all *all);
void			print_error_img(t_all *all);
void			angel_palyer(t_all *all, int *color, char **map, int *flag);
void			create_map(char **map, t_all *all);
void			free_sprite(t_all *all);
int				init_all(t_all *all, t_file file);
void			create_bmp(t_all *all);
void			init_sprite(t_all *all, double step);
void			print3d(t_all *all, double x, double y, double l);
void			reycast(t_all *all);
void			walking_help(t_all *all, double *x, double *y, int key);
int				chek_position(t_all *all, double *x2, double *y2);
void			ft_pars_help(t_file *file);
int				ft_open_file_help(int argc, char *argv[],
					t_file *file, int check_dot);
t_sprite		*sort_list(t_sprite *head);
int				check(double n1, double n2);

#endif

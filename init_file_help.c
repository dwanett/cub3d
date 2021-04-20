/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:29:56 by dwanetta          #+#    #+#             */
/*   Updated: 2021/04/20 17:29:47 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_pars_help(t_file *file)
{
	file->R_x = 0;
	file->R_y = 0;
	file->NO_texture = NULL;
	file->SO_texture = NULL;
	file->WE_texture = NULL;
	file->EA_texture = NULL;
	file->S_texture = NULL;
}

int	ft_open_file_help(int argc, char *argv[], t_file *file, int check_dot)
{
	int	size_argv;

	size_argv = ft_strlen(argv[1]) - 1;
	if (argv[1][size_argv - 3] != '.' || argv[1][size_argv - 2] != 'c'
	|| argv[1][size_argv - 1] != 'u'
	|| argv[1][size_argv] != 'b' || check_dot > 1)
	{
		ft_putstr_fd("Error\nInvalid file extension\n", 1);
		return (-1);
	}
	if (argc == 3)
	{
		if (argv[2][0] != '-' || argv[2][1] != '-' || argv[2][2] != 's'
			|| argv[2][3] != 'a' || argv[2][4] != 'v' || argv[2][5] != 'e')
		{
			ft_putstr_fd("Error\nInvalid two argument\n", 1);
			return (-1);
		}
		else
			file->check_save_image = 1;
	}
	return (0);
}

int	ft_pars_help2(int fd)
{
	char	*line;
	int		j;

	j = 1;
	while (j > 0)
	{
		j = get_next_line(fd, &line);
		if (line[0] != '\0')
		{
			ft_putstr_fd("Error\nInvalid_file\n", 1);
			return (-1);
		}
	}
	return (0);
}

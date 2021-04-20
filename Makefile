# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/15 01:41:01 by dwanetta          #+#    #+#              #
#    Updated: 2021/04/20 15:23:41 by dwanetta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
FLAGS = -Wall -Wextra -Werror
LIB = -L mlx_mac -L get_next_line -L libft
OPTION_LIB = -lmlx -framework OpenGL -framework AppKit -lgnl -lft
OPTION = -c -g
MLX = make -C mlx_mac
SRCS =	check_file_save_map.c \
		create_bmp.c \
		init_file.c \
		put_3d.c \
		sprite.c \
		utils_2.c \
		control.c \
		cub3d.c \
		init_struct_all.c \
		reycast.c \
		utils.c \
		move.c \
		init_file_help.c \
		sprite_utils.c

OBJS_SRCS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME) : $(OBJS_SRCS)
		@$(CC) $(FLAGS) $(OPTION) $(SRCS)
		@$(MLX)
		@$(CC) $(LIB) $(OPTION_LIB) $(OBJS_SRCS) -o $(NAME)
clean:
		rm -f $(OBJS_SRCS)
fclean: clean
		rm -f $(NAME)
		@$(MLX) clean
		rm -f *.bmp
re: fclean all
.PHONY: all clean fclean re

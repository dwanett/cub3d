NAME = libgnl.a
CC = gcc
FLAGS = -Wall -Wextra #-Werror
HEADER = get_next_line.h
OPTION = -c -I $(HEADER)
SRCS =	get_next_line.c\
		get_next_line_utils.c

OBJS_SRCS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME) : $(OBJS_SRCS)
		$(CC) $(FLAGS) $(OPTION) $(SRCS)
		ar rc $(NAME) $(OBJS_SRCS)
		ranlib $(NAME)

clean:
		rm -f $(OBJS_SRCS)
fclean: clean
		rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re bonus

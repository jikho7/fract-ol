###############
##
#Arguments

NAME	= fractol

###############
##
#Sources

SRCS	= fractol.c

OBJS	= ${SRCS:%.c=%.o}
CFLAGS	= -Werror -Wall -Wextra -g
CC		= gcc
RM		= rm -f
MAKE 	= make

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	$(MAKE) -C mlx
## -C change directory
	cp mlx/libmlx.dylib .
## copy libmlx dans le fichier ou l on est
	$(CC) $(CFLAGS) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

all: ${NAME}

clean:
	$(RM) $(OBJS)
	make clean -C mlx
	${RM} libmlx.dylib

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re



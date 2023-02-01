# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/01 17:17:52 by jdefayes          #+#    #+#              #
#    Updated: 2023/02/01 17:18:20 by jdefayes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###############
##
#Arguments
NAME	= fractol

###############
##
#Sources
SRCS	=	fractol.c\
			fractales.c\
			hooks.c\
			main.c\

OBJS	= ${SRCS:.c=.o}
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


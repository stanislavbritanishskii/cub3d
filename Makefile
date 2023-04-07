# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/21 20:12:24 by sbritani          #+#    #+#              #
#    Updated: 2023/04/07 23:00:27 by dhendzel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -I lib/include/ -I lib/ -I src/
CFLAGS	:= -I lib/include/ -I lib/ -I src/
LDFLAGS	:= -L ~/.brew/opt/glfw/lib/ -L ./libs/MLX42/ -L libs -lMLX42 -ldl -lglfw -lm -g
LDFLAGS	:= -L "$(shell brew --prefix glfw)/lib/" -L ./libs/MLX42/build -L libs -lMLX42 -ldl -lglfw -lm -g
OBJ_DIR	:= obj/
# HEADS	:=
NAME	:= cub3d

SRC		:= checks.c \
			main.c \
			read_map.c \
			utils.c dict.c \
			textures.c \
			init.c \
			color.c \
			draw_wall.c \
			clean.c \
			create_map.c \
			move_rotate.c \
			map_check.c \
			math_utils.c \
				

OBJ		:=	$(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC)))

libft_path=libs/libft/libft.a

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) libft
	$(CC) $(OBJ) $(libft_path) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)%.o: %.c 
	$(CC) $(CFLAGS) $< -c -o $@

$(OBJ_DIR): 
	mkdir obj

libft:
	make --directory=./libs/libft

norm:
	norminette $(SRC) cub.h

clean:
	make clean --directory=libs/libft/
	rm -f $(OBJ)
	rm -rf obj

fclean: clean
	make fclean --directory=libs/libft/
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


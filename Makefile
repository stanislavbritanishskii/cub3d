# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/21 20:12:24 by sbritani          #+#    #+#              #
#    Updated: 2023/04/08 00:12:11 by dhendzel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= gcc
FLAGS	:= -Wall -Wextra -Werror -I lib/include/ -I lib/ -I src/
FLAGS	:= -I lib/include/ -I lib/ -I src/
MLXLIB := libs/MLX42
LDFLAGS	:= -L ~/.brew/opt/glfw/lib/ -L $(MLXLIB) -L libs -lMLX42 -ldl -lglfw -lm -g
LDFLAGS	:= -L "$(shell brew --prefix glfw)/lib/" -L $(MLXLIB)/build -L libs -lMLX42 -ldl -lglfw -lm -g
OBJ_DIR	:= obj/
SRC_DIR	:= src/
# CMAKE = 
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
				
OBJS = $(FIL:.c=.o)
FIL =  $(addprefix src/, $(SRC)) 
libft_path=libs/libft/libft.a

all: libft libmlx $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS) 
	$(CC) $(OBJS) $(libft_path) $(LDFLAGS) -o $(NAME)


$(OBJS): %.o : %.c
	gcc $(CFLAGS) -c -o $@ $<
# $(OBJS): %.o: %.c 
# 	$(CC) $(FLAGS) $< -c -o $@

$(OBJ_DIR): 
	mkdir obj

libft:
	make --directory=./libs/libft

libmlx:
	cmake -B $(MLXLIB)/build $(MLXLIB)
	@$(MAKE) -C $(MLXLIB)/build
	
norm:
	norminette $(SRC) cub.h

clean:
	make clean --directory=libs/libft/
	rm -f $(OBJS)
	rm -rf obj

fclean: clean
	make fclean --directory=libs/libft/
	rm -rf $(MLXLIB)/build
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


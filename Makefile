# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/15 11:28:03 by kmieshko          #+#    #+#              #
#    Updated: 2018/08/15 11:28:04 by kmieshko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

SRCS = ./srcs/ft_addit_for_read.c \
		./srcs/ft_addit_for_rt.c \
		./srcs/ft_clamp.c \
		./srcs/ft_closest_intersection.c \
		./srcs/ft_count_params.c \
		./srcs/ft_create_camera.c \
		./srcs/ft_create_cone.c \
		./srcs/ft_create_cylinder.c \
		./srcs/ft_create_light.c \
		./srcs/ft_create_mlx.c \
		./srcs/ft_create_plane.c \
		./srcs/ft_create_rotation.c \
		./srcs/ft_create_sphere.c \
		./srcs/ft_error.c \
		./srcs/ft_intersect_cone.c \
		./srcs/ft_intersect_cylinder.c \
		./srcs/ft_intersect_plane.c \
		./srcs/ft_intersect_sphere.c \
		./srcs/ft_light.c \
		./srcs/ft_pixel_put.c \
		./srcs/ft_read_scene.c \
		./srcs/ft_trace_ray.c \
		./srcs/ft_vector_operations.c \
		./srcs/main.c

OBJ = $(SRCS:.c=.o)

LIB = ./libft/libft.a

INCL = -I ./include/

COMPILE = gcc -c

FLAGS = -Wall -Wextra -Werror

FLAGS_GR = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	gcc $(OBJ) $(FLAGS) $(FLAGS_GR) $(LIB) -o $(NAME)

%.o: %.c
	$(COMPILE) -o $@ $< $(FLAGS) $(INCL)
	
clean:
	make clean -C ./libft
	rm -rf $(OBJ)

fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)

re: fclean all
	make re -C ./libft
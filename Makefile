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

PATH_SRCS = ./srcs

SRCS = $(PATH_SRCS)/addit_for_read.c \
		$(PATH_SRCS)/error.c \
		$(PATH_SRCS)/find_value.c \
		$(PATH_SRCS)/ft_clamp.c \
		$(PATH_SRCS)/ft_closest_figure.c \
		$(PATH_SRCS)/ft_closest_intersection.c \
		$(PATH_SRCS)/ft_intersect_cone.c \
		$(PATH_SRCS)/ft_intersect_cylinder.c \
		$(PATH_SRCS)/ft_intersect_plane.c \
		$(PATH_SRCS)/ft_intersect_sphere.c \
		$(PATH_SRCS)/ft_light.c \
		$(PATH_SRCS)/ft_pixel_put.c \
		$(PATH_SRCS)/ft_reflect_ray.c \
		$(PATH_SRCS)/ft_trace_ray.c \
		$(PATH_SRCS)/ft_vector_operations.c \
		$(PATH_SRCS)/main.c \
		$(PATH_SRCS)/parse_scene.c \
		$(PATH_SRCS)/read_cone.c \
		$(PATH_SRCS)/read_cylinder.c \
		$(PATH_SRCS)/read_light.c \
		$(PATH_SRCS)/read_plane.c \
		$(PATH_SRCS)/read_scene.c \
		$(PATH_SRCS)/read_sphere.c \
		$(PATH_SRCS)/ft_clamp_with_param.c

OBJ = $(SRCS:.c=.o)

LIB = ./libft/libft.a

INCL = -I ./include/

INCL_FRM = -I ./frm/SDL2.framework/Headers/ \
		-I ./frm/SDL2_image.framework/Headers/ \
		-I ./frm/SDL2_ttf.framework/Headers/

FRMX = -F ./frm \
		-framework SDL2 \
		-framework SDL2_image \
		-framework SDL2_ttf \
		-framework OpenCL

FRMP = -rpath @loader_path/frm/

COMPILE = gcc -c

FLAGS = 

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	gcc $(FRMP) $(FRMX) $(OBJ) $(FLAGS) $(LIB) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
	$(COMPILE) -o $@ $< $(FLAGS) $(INCL) $(INCL_FRM)
	
clean:
	make clean -C ./libft
	rm -rf $(OBJ)

fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)

re: fclean all
	make re -C ./libft
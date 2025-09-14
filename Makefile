# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afantini <afantini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/06 10:16:07 by luigi             #+#    #+#              #
#    Updated: 2024/06/28 16:21:27 by afantini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            =   cub3D

CC              =   cc
CFLAGS			=	-g 
REQUIRED_CFLAGS	=	$(CFLAGS) -Wall -Wextra -Werror

LDFLAGS         =   -lm -lX11 -lXext
LIBFT           =   libft/libft.a
MINILIBX        =   minilibx/libmlx.a

BUILD_DIR		=	build
INC_DIR			=	$(BUILD_DIR)/inc
OBJS_DIR        =   $(BUILD_DIR)/obj
SRCS_DIR        =   src

SRCS			=	$(SRCS_DIR)/main.c \
					$(SRCS_DIR)/init.c \
                    $(SRCS_DIR)/utils_error_free_exit.c \
                    $(SRCS_DIR)/map_checking.c \
                    $(SRCS_DIR)/read_map_visual_data.c \
                    $(SRCS_DIR)/map_color.c \
                    $(SRCS_DIR)/read_map_cells.c \
                    $(SRCS_DIR)/render_texture_to_img.c \
                    $(SRCS_DIR)/raycasting_setup.c \
					$(SRCS_DIR)/raycasting_dda_setup.c \
                    $(SRCS_DIR)/pixel_line_draw_setup.c \
                    $(SRCS_DIR)/player_actions.c \
                    $(SRCS_DIR)/utils_general.c \
					$(SRCS_DIR)/utils_keys_management.c \
					$(SRCS_DIR)/utils_brightness.c
                    
OBJS			=	$(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

RM				=	rm -fr

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) $(MINILIBX) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(REQUIRED_CFLAGS) -c $< -o $@

clean:
	make clean -C libft
	$(RM) $(OBJS_DIR)
	$(RM) libft/get_next_line/*.o
	$(RM) cub3D

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)
    
re: fclean all

clear:
	clear

run: clear all
	$(NAME) $(ARGS)

mem: clear all
	valgrind --tool=$(VALGRIND-TOOL) $(VALGRIND-OPTIONS) $(NAME) $(ARGS)

vgdb: clear all
	valgrind --tool=$(VALGRIND-TOOL) $(VALGRIND-OPTIONS) --vgdb-error=0 $(NAME) $(ARGS)

gdb: clear all
	echo "target remote | vgdb\nc" > .gdbinit
	gdb --args $(NAME) $(ARGS)

debug: clear all
	gdb --args $(NAME) $(ARGS)

debugf: clear all
	vi .gdbinit && gdb --args $(NAME) $(ARGS)

.PHONY:
	all clean fclean re clear run mem vgdb gdb debug debugf

.SILENT:

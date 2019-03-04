# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: squiquem <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/23 19:01:27 by squiquem          #+#    #+#              #
#    Updated: 2018/02/05 19:54:54 by squiquem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY			:	all clean fclean re

NAME			=	fractol

SRC_DIR			=	./sources/

OBJ_DIR			=	./objects/

CPPFLAGS 		=	-I includes/

SRC_FILES		=	main.c \
					init.c \
					hook.c \
					draw.c \
					julia.c \
					mandelbrot.c \
					color.c \
					mouse.c \
					print.c \
					complex.c

OBJ_FILES		=	$(SRC_FILES:.c=.o)

SRC				=	$(addprefix $(SRC_DIR)/,$(SRC_FILES))

OBJ				=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

LFT				=	-L libft/ -lft

MLX				=	-L minilibx/ -lmlx -framework OpenGL -framework AppKit

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror

all				:	$(NAME)

$(NAME)			:	$(OBJ)
	@make -C libft/
	@make -C minilibx/
	@$(CC) $(CFLAGS) $(LFT) $(MLX) $(OBJ) -o $@ 
	@printf '\033[4m'
	@printf "\033[32m[ ✔ ] Fractol\n\033[0m"

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c
	@mkdir $(OBJ_DIR) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	@printf '\033[0m[ ✔ ] %s\n\033[0m' "$<"

clean			:
	@make fclean -C libft/
	@make clean -C minilibx/
	@rm -f $(OBJ)
	@rmdir $(OBJ_DIR) 2> /dev/null || true
	@printf '\033[4m'
	@echo "\033[31mFractol:\033[0m"
	@printf '\033[31m[ ✔ ] %s\n\033[0m' "Clean Object Files"

fclean			:	clean
	@rm -f $(NAME)
	@printf '\033[31m[ ✔ ] %s\n\033[0m' "Clean Binary File"

re				:	fclean all

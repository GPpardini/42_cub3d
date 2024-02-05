# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpardini <gpardini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 12:11:54 by gpardini          #+#    #+#              #
#    Updated: 2024/02/05 12:12:12 by gpardini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
FLAGS = -Wall -Werror -Wextra -g
MLXFLAGS	=	-L ./minilibx -lmlx -Ilmlx -lXext -lX11
MINILIBX_PATH	=	./minilibx
MINILIBX		=	$(MINILIBX_PATH)/libmlx.a
SRC = main.c

OBJ = $(SRC:%.c=%.o)

all: ${NAME}

${NAME}: $(OBJ)
	$(MAKE) --no-print-directory -C $(MINILIBX_PATH)
	$(CC) $(FLAGS) -lm $(SRC) $(MLXFLAGS) -o $(NAME)
	@rm *.o

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME) $(OBJ)

re: fclean all

.PHONY: all clean fclean re

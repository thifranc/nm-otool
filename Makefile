# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thifranc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/04 19:24:34 by thifranc          #+#    #+#              #
#    Updated: 2017/10/14 16:55:59 by thifranc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = nm

INC = nm-otool

SRCS = main_64

SRC_DIR = src/

INC_DIR = include/

SRCS:= $(addsuffix .c, $(SRCS))
SRCS:= $(addprefix $(SRC_DIR), $(SRCS))

INC:= $(addsuffix .h, $(INC))
INC:= $(addprefix $(INC_DIR), $(INC))

OBJ = $(SRCS:%.c=%.o)

FLAGS = -Wall -Werror -Wextra

OPT_FLAGS = 

all: $(NAME)

$(NAME):
	gcc $(FLAGS) $(SRCS) -I$(INC) -o $(NAME) $(OPT_FLAGS)

clean:
	@$(RM) $(OBJ)
	@echo "erasing all binary files"

fclean: clean
	@$(RM) $(NAME)
	@make clean -C libft/
	@echo "erasing $(NAME)"

re: fclean all
	@make fclean -C libft/
	@echo "fclean + all"

.PHONY: all clean fclean re

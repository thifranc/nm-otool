# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thifranc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/04 19:24:34 by thifranc          #+#    #+#              #
#    Updated: 2017/11/24 16:44:22 by thifranc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = src/
INC_DIR = include/

#executables name
NM = ft_nm
OTOOL = ft_otool

#includes and srcs
INC_NM = nm
SRCS_NM = swap sort main parser handle_macho handle_fat handle_64 handle_32 error utils

INC_OTOOL = otool
SRCS_OTOOL = 

#prefix and suffix
SRCS_NM:= $(addsuffix .c, $(SRCS_NM))
SRCS_NM:= $(addprefix $(SRC_DIR)nm/nm_, $(SRCS_NM))
INC_NM:= $(addsuffix .h, $(INC_NM))
INC_NM:= $(addprefix $(INC_DIR), $(INC_NM))
OBJ_NM = $(SRCS_NM:%.c=%.o)

SRCS_OTOOL:= $(addsuffix .c, $(SRCS_OTOOL))
SRCS_OTOOL:= $(addprefix $(SRC_DIR)ot_, $(SRCS_OTOOL))
INC_OTOOL:= $(addsuffix .h, $(INC_OTOOL))
INC_OTOOL:= $(addprefix $(INC_DIR), $(INC_OTOOL))
OBJ_OTOOL = $(SRCS_OTOOL:%.c=%.o)

#compilation flags
FLAGS = -Wall -Werror -Wextra

OPT_FLAGS = 

all: $(NM) $(OTOOL)

$(NM):
	gcc $(FLAGS) $(SRCS_NM) libft/libft.a -I$(INC_NM) -o $(NM) $(OPT_FLAGS)

$(OTOOL):
	gcc $(FLAGS) $(SRCS_OTOOL) -I$(INC_OTOOL) -o $(OTOOL) $(OPT_FLAGS)

nm: $(NM)
otool: $(OTOOL)

clean:
	@$(RM) $(OBJ_NM)
	@$(RM) $(OBJ_OTOOL)
	@echo "erasing all binary files"

fclean: clean
	@$(RM) $(OTOOL) $(NM)
	@make clean -C libft/

re: fclean all
	@make fclean -C libft/
	@echo "fclean + all"

.PHONY: all clean fclean re

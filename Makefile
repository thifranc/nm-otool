# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thifranc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/04 19:24:34 by thifranc          #+#    #+#              #
#    Updated: 2017/11/30 16:44:51 by thifranc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = src/
INC_DIR = include/
LIBPATH = libft/
LDFLAGS = -L $(LIBPATH) -lft

#executables name
NM = ft_nm
OTOOL = ft_otool

#includes and srcs
SRCS_NM = main\
	swap sort\
	parser handle_macho handle_lib\
	handle_fat handle_64 handle_32\
	error utils

SRCS_OTOOL = main\
	swap\
	parser handle_macho handle_lib\
	handle_fat handle_64 handle_32\
	error utils

#prefix and suffix
SRCS_NM:= $(addsuffix .c, $(SRCS_NM))
SRCS_OTOOL:= $(addsuffix .c, $(SRCS_OTOOL))

#objects files
OBJDIR = objs

NM_OBJS = $(patsubst %.c, $(OBJDIR)/nm/%.o, $(SRCS_NM))
OTOOL_OBJS = $(patsubst %.c, $(OBJDIR)/otool/%.o, $(SRCS_OTOOL))


#compilation flags
FLAGS = -Wall -Werror -Wextra

#paths
NM_PATH:= src/nm/
OTOOL_PATH:= src/otool/

$(OBJDIR)/nm/%.o: $(NM_PATH)nm_%.c
	@gcc $(FLAGS) -o $@ -c $< -I $(LIBPATH) -I $(INC_DIR)

$(OBJDIR)/otool/%.o: $(OTOOL_PATH)ot_%.c
	@gcc $(FLAGS) -o $@ -c $< -I $(LIBPATH) -I $(INC_DIR)

all: $(NM) $(OTOOL)

$(NM): $(NM_OBJS)
	@make -C $(LIBPATH)
	@gcc $(FLAGS) $(LDFLAGS) -o $(NM) $(NM_OBJS)

$(OTOOL): $(OTOOL_OBJS)
	@make -C $(LIBPATH)
	@gcc $(FLAGS) $(LDFLAGS) -o $(OTOOL) $(OTOOL_OBJS)

$(LIB):
	@make -C $(LIBPATH)


nm: $(LIB) $(NM)
otool: $(LIB) $(OTOOL)

clean:
	@make clean -C libft/
	@$(RM) $(NM_OBJS)
	@$(RM) $(OTOOL_OBJS)

fclean: clean
	@make fclean -C libft/
	@$(RM) $(OTOOL) $(NM)

re: fclean all

.PHONY: all clean fclean re

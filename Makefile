#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/26 16:31:33 by ddinaut           #+#    #+#              #
#    Updated: 2019/02/28 23:07:32 by ddinaut          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

# Output file #
NAME		= libft_malloc_$(HOSTTYPE).so
SMB_LINK	= libft_malloc.so

# Details #
CC		= gcc
FLAGS	= -Wall -Wextra -Werror #-Wpadded
DEB		= #-fsanitize=address

# Directories
OBJ_DIR = .obj
SRC_DIR = srcs
INC_DIR = includes

LIBFT		= -Ilibft/includes/ -Llibft/ -lft
LIBPRINTF	= -Ift_printf/includes/ -Lft_printf/ -lftprintf

# Colors #
COL_BLACK	= \033[1;30m
COL_RED		= \033[1;31m
COL_GREEN	= \033[1;32m
COL_YELLOW	= \033[1;33m
COL_BLUE	= \033[1;34m
COL_PURPLE	= \033[1;35m
COL_WHITE	= \033[1;37m
CLEAN_LINE	= \033[K
END_COL		= \033[0;m

# Sources #
SRCS =					\
	malloc.c			\
	manage_chunk.c		\
	search_chunk.c		\
	create_area.c		\
						\
	realloc.c			\
	realloc_utils.c		\
	calloc.c			\
	free.c				\
	free_utils.c		\
						\
	utils.c				\
	generate_checksum.c	\
	manage_checksum.c	\
	thread_protection.c \
	show_alloc_mem.c

OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
SRC_FILES = $(addprefix $(SRC_DIR)/,$(SRCS))

#OBJ_FILES = $(SRC_FILES:%.c=%.o)

# Rules #
.PHONY: all clean fclean re libft ft_printf test

all: $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(FLAGS) -fPIC -o $@ -c $< -I$(INC_DIR)

$(NAME): libft ft_printf $(OBJ_FILES)
	$(CC) $(FLAG) $(DEB) -shared -o $(NAME) $(OBJ_FILES) -I$(INC_DIR) $(LIBFT) $(LIBPRINTF)
	rm -f $(SMB_LINK)
	ln -s $(NAME) $(SMB_LINK)

libft:
	@printf "[Compiling libft] :\n"
#	make -C libft/

ft_printf:
	@printf "\n[Compiling ft_printf] :\n"
#	make -C ft_printf/

test: all
	$(CC) test/aleatory.c -o aleatory $(NAME) -I$(INC_DIR) $(LIBPRINTF) $(LIBFT)

clean:
	/bin/rm -f $(OBJ_FILES)
#	make -C libft/ clean
#	make -C ft_printf/ clean

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(SMB_LINK)
#	make -C libft/ fclean
#	make -C ft_printf/ fclean

re: fclean all

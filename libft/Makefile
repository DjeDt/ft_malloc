#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/04 19:43:04 by ddinaut           #+#    #+#              #
#    Updated: 2018/02/28 15:11:11 by ddinaut          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

# Output file #
NAME = libft.a

# Details #
CC		= gcc
FLAGS	= -Wall -Wextra -Werror

# Path #
OBJ_PATH = .obj
SRC_PATH = srcs
INC_PATH = includes/

# Sub_dirs #
STR		= str/
MEM		= mem/
ARRAY	= array/
LIST	= list/
CONV	= conversion/
PRINT	= print/
UTIL	= utils/
TREE	= tree/

# More sub_dir #
BTREE = $(TREE)binary_tree/
RBTREE = $(TREE)rb_tree/

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
SRCS = \
	$(PRINT)ft_putchar.c $(PRINT)ft_putchar_fd.c $(PRINT)ft_putendl.c \
	$(PRINT)ft_putendl_fd.c $(PRINT)ft_putnbr.c $(PRINT)ft_putnbr_fd.c \
	$(PRINT)ft_putstr.c $(PRINT)ft_putstr_fd.c $(PRINT)ft_print_binary.c \
	$(PRINT)ft_putstr_col.c $(PRINT)ft_putendl_col.c $(PRINT)ft_putendl_col_fd.c \
\
	$(STR)ft_strcat.c $(STR)ft_strchr.c $(STR)ft_strreplace.c $(STR)ft_strclr.c \
	$(STR)ft_strcmp.c $(STR)ft_strcpy.c $(STR)ft_strdel.c $(STR)ft_strdup.c $(STR)ft_strndup.c \
	$(STR)ft_strequ.c $(STR)ft_striter.c $(STR)ft_striteri.c $(STR)ft_strjoin.c $(STR)ft_strjoin_fl.c \
	$(STR)ft_strjoin_fr.c $(STR)ft_strjoin_fb.c $(STR)ft_strlcat.c $(STR)ft_strlen.c \
	$(STR)ft_strnlen.c $(STR)ft_strmap.c $(STR)ft_strmapi.c $(STR)ft_strncat.c $(STR)ft_strncmp.c \
	$(STR)ft_strncpy.c $(STR)ft_strnequ.c $(STR)ft_strnew.c $(STR)ft_strnstr.c $(STR)ft_strrchr.c \
	$(STR)ft_strsplit.c $(STR)ft_strstr.c $(STR)ft_strsub.c $(STR)ft_strtrim.c $(STR)ft_bzero.c \
	$(STR)ft_strfsub.c $(STR)ft_strtok.c \
\
	$(UTIL)ft_isdigit.c $(UTIL)ft_isalnum.c $(UTIL)ft_isascii.c $(UTIL)ft_isprint.c $(UTIL)ft_isspace.c \
	$(UTIL)ft_count_char.c $(UTIL)get_next_line.c $(UTIL)ft_isalpha.c $(UTIL)ft_tolower.c $(UTIL)ft_toupper.c \
	$(UTIL)open_file.c \
\
	$(MEM)ft_memcpy.c $(MEM)ft_memccpy.c $(MEM)ft_memset.c $(MEM)ft_memmove.c $(MEM)ft_memchr.c \
	$(MEM)ft_memcmp.c $(MEM)ft_memalloc.c $(MEM)ft_memdel.c \
\
	$(ARRAY)ft_arrdup.c $(ARRAY)ft_arrjoin.c $(ARRAY)ft_arrprint.c $(ARRAY)ft_arrfree.c \
	$(ARRAY)ft_arrlen.c $(ARRAY)ft_split_whitespaces.c $(ARRAY)ft_arrldup.c $(ARRAY)ft_arrfjoin.c \
\
	$(CONV)ft_itoa.c $(CONV)ft_itoa_base.c $(CONV)ft_atoi.c \
\
	$(LIST)ft_lstadd.c $(LIST)ft_lstdel.c $(LIST)ft_lstdelone.c $(LIST)ft_lstiter.c \
	$(LIST)ft_lstmap.c $(LIST)ft_lstnew.c \
\
	$(BTREE)btree_apply_by_lvl.c $(BTREE)btree_apply_infix.c $(BTREE)btree_apply_prefix.c \
	$(BTREE)btree_apply_suffix.c $(BTREE)btree_create_node.c $(BTREE)btree_insert_data.c \
	$(BTREE)btree_lvl_count.c $(BTREE)btree_search_item.c $(BTREE)count_node.c \
\
	$(RBTREE)compare.c $(RBTREE)deletion.c $(RBTREE)family.c $(RBTREE)insert_case.c $(RBTREE)rotate.c \
	$(RBTREE)search_node.c $(RBTREE)insert_node.c

AR	= ar rc $(NAME)
RAN = ranlib $(NAME)
INC = -I$(INC_PATH)

OBJ = $(SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)
SRC = $(addprefix $(SRC_PATH)/,$(SRCS))

# Rules #
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(OBJ)
	$(RAN)

$(OBJ): $(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	mkdir -p $(dir $@)
	$(CC) -o $@ $(FLAGS) $(E_FLAGS) $(INC) -c $<

clean:
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

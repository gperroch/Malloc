# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpaulmye <tpaulmye@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/08/14 09:17:27 by tpaulmye          #+#    #+#              #
#    Updated: 2017/09/19 14:10:09 by gperroch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME_MALLOC = libft_malloc_$(HOSTTYPE).so
NAME_MALLOC_LINK = libft_malloc.so

SRC_MALLOC_PATH = ./SOURCES/
SRC_MALLOC_NAME =	malloc.c \
					free.c \
					dump_mem.c \
					realloc.c \
					show_alloc_mem.c \
					ft_new_area.c

OBJ_MALLOC_PATH = ./OBJECTS/
INC_PATH = ./INCLUDES/
LIBFT = libft/libftprintf.a
LIB_PATH = ./libft/
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIC -g

OBJ_MALLOC_NAME = $(SRC_MALLOC_NAME:.c=.o)
OBJ_MALLOC = $(addprefix $(OBJ_MALLOC_PATH),$(OBJ_MALLOC_NAME))

LIB = $(addprefix -L,$(LIB_PATH))
INC = $(addprefix -I,$(INC_PATH))
LDFLAGS = $(LIB)

.PHONY: all clean fclean re libft

all: $(LIBFT) $(NAME_MALLOC)

$(NAME_MALLOC): $(LIBFT) $(OBJ_MALLOC)
	$(CC) $^ -shared -o $@ $(LDFLAGS)
	@echo "$(NAME_MALLOC) complete ! 🍻 "
	ln -s $(NAME_MALLOC) $(NAME_MALLOC_LINK)

$(OBJ_MALLOC_PATH)%.o: $(SRC_MALLOC_PATH)%.c
	@mkdir $(OBJ_MALLOC_PATH) 2> /dev/null || echo  > /dev/null
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	rm -rf $(OBJ_MALLOC)
	rmdir $(OBJ_MALLOC_PATH) obj 2> /dev/null || echo  > /dev/null
	make clean -C $(LIB_PATH)

fclean: clean
	rm -rf $(NAME_MALLOC) $(NAME_MALLOC_LINK)
	make fclean -C $(LIB_PATH)
	@echo "Everything's clean, master !"

re: fclean all

$(LIBFT):
	make -j4 -C $(LIB_PATH)

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpaulmye <tpaulmye@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/08/14 09:17:27 by tpaulmye          #+#    #+#              #
#    Updated: 2017/09/12 14:24:01 by gperroch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_COREWAR = malloc.out

SRC_COREWAR_PATH = ./SOURCES/
SRC_COREWAR_NAME =	main.c \
					malloc.c \
					free.c \
					dump_mem.c \
					realloc.c \
					show_alloc_mem.c

OBJ_COREWAR_PATH = ./OBJECTS/
INC_PATH = ./INCLUDES/
LIBFT = LIBFTPRINTF/LIBFTPRINTF.a
LIB_PATH = ./LIBFTPRINTF/
#LIB_NAMES = -lft
CC = gcc
#CFLAGS = -Wall -Wextra -Werror

OBJ_COREWAR_NAME = $(SRC_COREWAR_NAME:.c=.o)
OBJ_COREWAR = $(addprefix $(OBJ_COREWAR_PATH),$(OBJ_COREWAR_NAME))

LIB = $(addprefix -L,$(LIB_PATH))
INC = $(addprefix -I,$(INC_PATH))
LDFLAGS = $(LIB) #$(LIB_NAMES)

.PHONY: all clean fclean re libft

all: $(LIBFT) $(NAME_COREWAR)

$(NAME_COREWAR): $(LIBFT) $(OBJ_COREWAR)
	@$(CC) $^ -o $@ $(LDFLAGS)
	@echo "$(NAME_COREWAR) complete ! 🍻 "

$(OBJ_COREWAR_PATH)%.o: $(SRC_COREWAR_PATH)%.c
	@mkdir $(OBJ_COREWAR_PATH) 2> /dev/null || echo  > /dev/null
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@rm -rf $(OBJ_COREWAR)
	@rmdir $(OBJ_COREWAR_PATH) obj 2> /dev/null || echo  > /dev/null
	@make clean -C LIBFTPRINTF

fclean: clean
	@rm -rf $(NAME_COREWAR)
	@make fclean -C LIBFTPRINTF
	@echo "Everything's clean, master !"

re: fclean all

$(LIBFT):
	make -j4 -C LIBFTPRINTF

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/20 10:33:01 by gperroch          #+#    #+#              #
#    Updated: 2017/03/28 10:25:47 by gperroch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=				malloc.out

SOURCES_FILES=		malloc.c 	\
					free.c		\
					realloc.c

OBJECTS_FILES=		$(SOURCES_FILES:.c=.o)

SOURCES_FOLDER=		./SOURCES/

OBJECTS_FOLDER=		./OBJECTS/

SOURCES=$(addprefix $(SOURCES_FOLDER),$(SOURCES_FILES))
OBJECTS=$(addprefix $(OBJECTS_FOLDER),$(OBJECTS_FILES))

COMPILATOR_FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS)
	gcc $^ -o $@ -L LIBFTPRINTF

$(OBJECTS_FOLDER)%.o: $(SOURCES_FOLDER)%.c
	mkdir $(OBJECTS_FOLDER) 2> /dev/null || echo > /dev/null
	gcc -c $< -o $@ -I INCLUDES

clean:
	rm $(OBJECTS)

fclean: clean
	rm $(NAME)

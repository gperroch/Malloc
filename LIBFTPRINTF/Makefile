# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gperroch <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/28 11:14:25 by gperroch          #+#    #+#              #
#    Updated: 2016/04/08 14:55:48 by gperroch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CFLAGS = -Wall -Wextra -Werror

SRC_PATH = ./

OBJ_PATH = ./

LIB_PATH = ./

INC_PATH = ./

SRC_NAMES =	ft_isprint.c \
			ft_memdel.c	\
	  		ft_putnbr_fd.c \
	   		ft_strdel.c	\
	   		ft_strmapi.c \
   	  		ft_strstr.c \
	 		ft_atoi.c \
	   		ft_itoa.c \
	   		ft_memmove.c \
   	   		ft_putstr.c \
   	   		ft_strdup.c \
   	   		ft_strncat.c \
   	   		ft_strsub.c \
	   		ft_memset.c \
   	   		ft_putstr_fd.c \
   	   		ft_strequ.c \
   	   		ft_strncmp.c \
   	   		ft_strtrim.c \
	   		ft_bzero.c \
	   		ft_memalloc.c \
   	   		ft_putchar.c \
   	   		ft_strcat.c \
   	   		ft_striter.c \
   	   		ft_strncpy.c \
   	   		ft_tolower.c \
	   		ft_isalnum.c \
   	   		ft_memccpy.c \
   	   		ft_putchar_fd.c \
   	   		ft_strchr.c \
   	   		ft_striteri.c \
   	   		ft_strnequ.c \
   	   		ft_toupper.c \
	   		ft_isalpha.c \
   	   		ft_memchr.c \
   	   		ft_putendl.c \
   	   		ft_strclr.c \
   	   		ft_strlcat.c \
   	   		ft_strnew.c \
	   		ft_isascii.c \
   	   		ft_memcmp.c \
   	   		ft_putendl_fd.c \
   	   		ft_strcmp.c	\
	   		ft_strlen.c	\
	   		ft_strnstr.c \
	   		ft_isdigit.c \
   	   		ft_memcpy.c	\
	   		ft_putnbr.c	\
	   		ft_strcpy.c	\
	   		ft_strmap.c	\
	   		ft_strrchr.c \
			ft_strsplit.c \
			ft_strjoin.c \
			ft_lstiter.c \
			ft_lstnew.c \
			ft_lstdelone.c \
			ft_lstdel.c \
			ft_lstadd.c \
			ft_lstmap.c \
			ft_lstlen.c \
			ft_lstdup.c \
			ft_strlenchr.c \
			ft_strdupchr.c \
			ft_strndup.c \
			ft_sqrt.c \
			ft_tabjoin_int.c \
			ft_tabjoin_str.c \
			ft_freetab_str.c \
			ft_printf.c \
			ft_print_conv.c	\
			ft_print_extra.c \
			ft_swap.c \
			ft_print_integers.c	\
			ft_print_ptr.c \
			ft_close_regex.c \
			ft_print_regex.c \
			ft_print_specifier.c \
			ft_modif_flags.c \
			ft_itoabase.c \
			ft_itoabase_unsigned.c \
			ft_bitoint.c \
			ft_power.c \
			ft_wchar_display.c \
			ft_intostring.c \
			ft_precision.c \
			ft_freetab_str.c \
			ft_printtab_str.c \
			ft_tabjoin_str.c \
			ft_tablen_str.c \
			ft_freetab_int.c \
			ft_printtab_int.c \
			ft_tabjoin_int.c \
			ft_tabjoin_tabstr.c \
			get_next_line.c
			
OBJ_NAMES =	$(SRC_NAMES:.c=.o)

INC_NAMES = libftprintf.h

SRC	= $(addprefix $(SRC_PATH)/,$(SRC_NAMES))
OBJ	= $(addprefix $(OBJ_PATH)/,$(OBJ_NAMES))

all : $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ_NAMES)
	@ranlib $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@gcc $(CFLAGS) -c $<

clean : 
	@rm -f $(OBJ_NAMES)

fclean : clean
	@rm -f $(NAME)

re : fclean all

norme :
	@norminette $(SRC_NAMES)
	@norminette $(INC_NAMES)

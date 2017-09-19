/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 10:35:58 by gperroch          #+#    #+#             */
/*   Updated: 2016/02/17 10:43:14 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>
# include <wchar.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include "libft.h"

void			ft_close_regex(char *restrict *format, char specifier);
int				ft_print_regex(char *restrict *format, va_list ap);
char			*ft_print_conv(char *format, va_list ap, char specifier);
char			*ft_print_extra(char *format, char **regex_printed,
		char specifier);
char			*ft_print_integers(char *convchars, va_list ap);
char			*ft_print_ptr(char *convchars, va_list ap);
char			*ft_itoabase(intmax_t nb, int base);
char			*ft_itoabase_unsigned(uintmax_t nb, int base);
void			ft_swap(char *a, char *b);
char			ft_print_specifier(char *format);
void			ft_modif_flags(char *format, char **regex_printed,
		char specifier, char *flags);
int				ft_fieldwidth(char *format, char **regex_printed,
		char specifier);

#endif

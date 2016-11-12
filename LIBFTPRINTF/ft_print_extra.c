/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 17:22:08 by gperroch          #+#    #+#             */
/*   Updated: 2016/03/13 13:58:14 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			ft_fieldwidth(char *format, char **regex_printed, char specifier)
{
	char	*field_add;
	char	*tmp;
	int		len;
	int		fieldwidth;

	while ((*format == '+' || *format == '-' || *format == ' '
				|| *format == '#' || *format == '0')
			&& *format != specifier)
		format++;
	fieldwidth = ft_atoi(format);
	((specifier == 'c' || specifier == 'C')
		&& !ft_strlen(*regex_printed)) ? (fieldwidth--) : (0);
	len = fieldwidth - ft_strlen(*regex_printed);
	if (len <= 0)
		return (0);
	tmp = ft_memset(ft_strnew(len), ' ', len);
	field_add = ft_strjoin(tmp, *regex_printed);
	free(tmp);
	*regex_printed = ft_strdup(field_add);
	free(field_add);
	return (fieldwidth);
}

static void	ft_flags(char *format, char speci, int precision, char *flags)
{
	while (*format != speci)
	{
		if (*format == '#' && (speci == 'x' || speci == 'X'
					|| speci == 'o' || speci == 'O'))
			flags[0] = 1;
		if (*format == '0' && (format[-1] < '0' || format[-1] > '9'))
			flags[1] = 1;
		if (*format == '-')
			flags[2] = 1;
		if (*format == '+' && speci != 'u')
			flags[3] = 1;
		if (*format == ' ' && speci != 'u')
			flags[4] = 1;
		format++;
	}
	if (precision > 0 && (speci == 'o' || speci == 'O'))
		flags[0] = 0;
	if (flags[2] == 1 || (precision && (speci == 'i' || speci == 'd'
					|| speci == 'D' || speci == 'o' || speci == 'O'
					|| speci == 'x' || speci == 'X' || speci == 'u'
					|| speci == 'U')))
		flags[1] = 0;
	if (flags[3] == 1 || speci == '%' || speci == 'o' || speci == 'O'
			|| speci == 'x' || speci == 'X' || speci == 'p')
		flags[4] = 0;
}

char		*ft_print_extra(char *format, char **regex_printed,
		char specifier, int size_s)
{
	int		i;
	int		precision;
	int		fieldwidth;
	char	flags[5];

	i = -1;
	ft_memset(&flags[0], 0, 5);
	precision = ft_precision(format, regex_printed, specifier, size_s);
	fieldwidth = ft_fieldwidth(format, regex_printed, specifier);
	ft_flags(format, specifier, precision, flags);
	ft_modif_flags(format, regex_printed, specifier, flags);
	return (*regex_printed);
}

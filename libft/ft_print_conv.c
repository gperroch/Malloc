/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_conv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 09:06:14 by gperroch          #+#    #+#             */
/*   Updated: 2016/03/13 12:55:46 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	ft_upper_conv(char *convchars)
{
	if (convchars[0] != 'D' && convchars[0] != 'O' && convchars[0] != 'U'
			&& convchars[0] != 'S' && convchars[0] != 'C')
		return ;
	convchars[0] = convchars[0] + 32;
	convchars[2] = convchars[1];
	convchars[1] = 'l';
	if (convchars[2] != 'l')
		convchars[2] = 0;
}

static void	ft_convchars(char *format, char *convchars, char specifier)
{
	int		i;
	int		j;

	j = 0;
	i = -1;
	while (format[i] != specifier)
		i++;
	while (format[--i] != '%')
	{
		if (format[i] == 'l' || format[i] == 'h'
				|| format[i] == 'j' || format[i] == 'z')
			convchars[++j] = format[i];
	}
	if ((convchars[2] == 'z' && convchars[1] == 'h')
			|| (convchars[1] == 'z' && convchars[2] == 'h'))
		convchars[1] = 'z';
	if ((convchars[2] == 'j' && convchars[1])
			|| (convchars[1] == 'j' && convchars[2]))
		convchars[1] = 'j';
	if (convchars[1] != convchars[2] || convchars[1] == 'j'
			|| convchars[1] == 'z')
		convchars[2] = 0;
}

char		*ft_print_conv(char *format, va_list ap, char specifier,
		int *size_s)
{
	char	*convchars;
	char	*regex;
	int		i;

	i = 0;
	regex = NULL;
	convchars = ft_strnew(3);
	convchars[0] = specifier;
	ft_convchars(format, convchars, specifier);
	ft_upper_conv(convchars);
	if (convchars[0] == 's' || convchars[0] == 'p')
		return (ft_print_ptr(convchars, ap, size_s));
	else
		return (ft_print_integers(convchars, ap));
}

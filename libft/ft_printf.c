/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 18:05:12 by gperroch          #+#    #+#             */
/*   Updated: 2016/02/17 10:59:31 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			ft_printf(char *restrict format, ...)
{
	va_list	ap;
	int		printed;
	int		j;

	va_start(ap, format);
	printed = 0;
	while (*format)
	{
		j = 0;
		while (format[j] != '%' && format[j] != '\0')
			j++;
		printed += j;
		write(1, format, j);
		while (--j >= 0)
			format++;
		if (*format == '%')
			printed += ft_print_regex(&format, ap);
	}
	va_end(ap);
	return (printed);
}

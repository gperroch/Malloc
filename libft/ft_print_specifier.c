/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_specifier.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/13 08:25:47 by gperroch          #+#    #+#             */
/*   Updated: 2016/02/17 10:59:18 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char		ft_print_specifier(char *format)
{
	int		i;

	i = -1;
	while (format[++i] == ' ' || format[i] == '#' || format[i] == '+'
			|| format[i] == '-' || format[i] == '.' || format[i] == 'l'
			|| format[i] == 'h' || format[i] == 'j' || format[i] == 'z'
			|| (format[i] <= '9' && format[i] >= '0'))
		;
	return (format[i]);
}

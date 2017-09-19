/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_regex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 10:50:13 by gperroch          #+#    #+#             */
/*   Updated: 2016/03/13 13:10:10 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		ft_close_regex(char *restrict *format, char specifier)
{
	while (**format != specifier)
		(*format)++;
	if (specifier)
		(*format)++;
	return ;
}

int			ft_wrong_specifier(char c)
{
	if (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D')
		return (0);
	if (c == 'i' || c == 'o' || c == 'O' || c == 'u' || c == 'U')
		return (0);
	if (c == 'x' || c == 'X' || c == 'c' || c == 'C' || c == '%')
		return (0);
	return (1);
}

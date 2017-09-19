/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 09:49:35 by gperroch          #+#    #+#             */
/*   Updated: 2016/03/13 13:39:27 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>
#include <locale.h>

char				*ft_wchar_display(uintmax_t arg)
{
	int				len;
	unsigned int	value;

	value = arg;
	len = ft_strlen(ft_itoabase_unsigned(value, 2));
	if (len < 8)
		return (ft_one(value));
	else if (len < 12)
		return (ft_two(value));
	else if (len < 17)
		return (ft_three(value));
	else
		return (ft_four(value));
}

char				*ft_one(unsigned int value)
{
	char			*regex_printed;

	if (!(regex_printed = ft_strnew(2)))
		return (NULL);
	regex_printed[0] = value;
	return (regex_printed);
}

char				*ft_two(unsigned int value)
{
	int				mask[2];
	int				cursor;
	int				nb;

	mask[0] = 0x80;
	mask[1] = 0xC0;
	cursor = 1;
	nb = 0;
	while (++nb < 12)
	{
		if (nb < 7 && (cursor & value))
			mask[0] = mask[0] | cursor;
		if (nb >= 7 && (cursor & value))
		{
			mask[1] = mask[1] << 6;
			mask[1] = mask[1] | cursor;
			mask[1] = mask[1] >> 6;
		}
		cursor = cursor << 1;
	}
	return (ft_intostring(mask, 2));
}

char				*ft_three(unsigned int value)
{
	int				mask[3];
	int				cursor;
	int				nb;

	mask[0] = 0x80;
	mask[1] = 0x80;
	mask[2] = 0xE0;
	cursor = 1;
	nb = 0;
	while (++nb < 17)
	{
		mask[0] = (nb < 7 && (cursor & value)) ? (mask[0] | cursor) : mask[0];
		mask[1] = (nb < 13 && (cursor & value)) ? (mask[1] << 6) : mask[1];
		mask[1] = (nb < 13 && (cursor & value)) ? (mask[1] | cursor) : mask[1];
		mask[1] = (nb < 13 && (cursor & value)) ? (mask[1] >> 6) : mask[1];
		mask[2] = (nb >= 13 && (cursor & value)) ? (mask[2] << 12) : mask[2];
		mask[2] = (nb >= 13 && (cursor & value)) ? (mask[2] | cursor) : mask[2];
		mask[2] = (nb >= 13 && (cursor & value)) ? (mask[2] >> 12) : mask[2];
		cursor = cursor << 1;
	}
	return (ft_intostring(mask, 3));
}

char				*ft_four(unsigned int value)
{
	int				mask[4];
	int				cursor;
	int				nb;

	mask[0] = 0x80;
	mask[1] = 0x80;
	mask[2] = 0x80;
	mask[3] = 0xF0;
	cursor = 1;
	nb = 0;
	while (++nb < 22)
	{
		mask[0] = (nb < 7 && (cursor & value)) ? (mask[0] | cursor) : mask[0];
		mask[1] = (nb < 13 && (cursor & value)) ? (mask[1] << 6) : mask[1];
		mask[1] = (nb < 13 && (cursor & value)) ? (mask[1] | cursor) : mask[1];
		mask[1] = (nb < 13 && (cursor & value)) ? (mask[1] >> 6) : mask[1];
		mask[2] = (nb < 19 && (cursor & value)) ? (mask[2] << 12) : mask[2];
		mask[2] = (nb < 19 && (cursor & value)) ? (mask[2] | cursor) : mask[2];
		mask[2] = (nb < 19 && (cursor & value)) ? (mask[2] >> 12) : mask[2];
		mask[3] = (nb >= 19 && (cursor & value)) ? (mask[3] << 18) : mask[3];
		mask[3] = (nb >= 19 && (cursor & value)) ? (mask[3] | cursor) : mask[3];
		mask[3] = (nb >= 19 && (cursor & value)) ? (mask[3] >> 18) : mask[3];
		cursor = cursor << 1;
	}
	return (ft_intostring(mask, 4));
}

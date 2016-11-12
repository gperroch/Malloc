/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intostring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 13:17:41 by gperroch          #+#    #+#             */
/*   Updated: 2016/03/13 13:57:51 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char			*ft_intostring(int *mask, int size)
{
	char		*regex_printed;
	int			cursor;
	int			len;
	int			i;
	int			shift;

	len = 4 * size;
	regex_printed = ft_strnew(size + 1);
	cursor = 1;
	size--;
	shift = 0;
	i = 0;
	while (size >= 0)
	{
		if (cursor & mask[size])
			regex_printed[i] = regex_printed[i] | mask[size];
		cursor = (cursor < 128) ? (cursor << 1) : 1;
		(cursor == 128) ? shift++ : 0;
		mask[size] = (cursor == 128) ? (mask[size] >> 8) : (mask[size]);
		(regex_printed[i] && cursor == 128) ? i++ : 0;
		(shift == 4) ? size-- : 0;
		shift = (shift == 4) ? 0 : shift;
	}
	return (regex_printed);
}

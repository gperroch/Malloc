/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitoint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:57:35 by gperroch          #+#    #+#             */
/*   Updated: 2016/03/10 16:12:09 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			ft_bitoint(char *str)
{
	int		res;
	int		mask;
	int		len;
	int		i;

	len = ft_strlen(str);
	i = -1;
	res = 0;
	mask = 0x1;
	while (++i < 32)
	{
		if (str[len - i - 1] == '1')
			res = res | mask;
		mask = mask << 1;
	}
	return (res);
}

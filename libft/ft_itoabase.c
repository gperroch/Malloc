/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itaobase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 16:11:49 by gperroch          #+#    #+#             */
/*   Updated: 2016/02/17 10:53:24 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>

char			*ft_itoabase(intmax_t num, int base)
{
	int			i;
	int			isnegative;
	intmax_t	rem;
	char		*str;

	i = 0;
	rem = num;
	isnegative = 0;
	if (num == 0)
		return (ft_memset(ft_strnew(1), '0', 1));
	while ((rem = rem / base) != 0)
		i++;
	str = ft_strnew(i + 1);
	(num < 0 && base != 16) ? (isnegative = 1) : (0);
	(isnegative == 1) ? (num = -num) : (0);
	while (num != 0)
	{
		rem = num % base;
		str[i--] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / base;
	}
	if (isnegative)
		str = ft_strjoin("-", str);
	return (str);
}

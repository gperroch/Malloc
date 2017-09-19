/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printtab_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 10:44:03 by gperroch          #+#    #+#             */
/*   Updated: 2016/03/16 11:59:01 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		ft_printtab_int(int *tab, int length, char *separator)
{
	int		i;

	i = -1;
	if (!tab)
		return ;
	while (++i < length)
	{
		ft_putnbr(tab[i]);
		if (i < length - 1)
			write(1, separator, ft_strlen(separator));
	}
}

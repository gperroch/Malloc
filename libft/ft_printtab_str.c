/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printtab_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 10:37:19 by gperroch          #+#    #+#             */
/*   Updated: 2016/03/25 12:43:59 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		ft_printtab_str(char **tab, int length, char *separator)
{
	int		i;
	int		nb;

	i = -1;
	nb = 0;
	if (length >= 0)
		nb = length;
	while (length < 0 && tab[++i])
		nb++;
	i = -1;
	while (++i < nb)
	{
		ft_putstr(tab[i]);
		if (tab[i][0] && i < nb - 1)
			write(1, separator, ft_strlen(separator));
	}
}

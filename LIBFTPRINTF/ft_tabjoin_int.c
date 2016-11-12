/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabjoin_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 09:51:18 by gperroch          #+#    #+#             */
/*   Updated: 2016/05/16 15:10:57 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdlib.h>

int			*ft_tabjoin_int(int **tab, int length, int nbr)
{
	int		*new_tab;

	new_tab = NULL;
	if (length < 0)
		return (NULL);
	if (!*tab)
		length = 0;
	if (!(new_tab = (int *)malloc(sizeof(int) * (length + 1))))
		return (NULL);
	new_tab[length] = nbr;
	while (--length >= 0)
		new_tab[length] = (*tab)[length];
	free(*tab);
	*tab = new_tab;
	return (new_tab);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 10:15:06 by gperroch          #+#    #+#             */
/*   Updated: 2016/03/16 11:40:55 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdlib.h>

void	ft_freetab_int(int **tab, int length)
{
	int	i;

	i = -1;
	if (!tab)
		return ;
	while (tab[++i] && (i < length || length < 0))
	{
		free(tab[i]);
		tab[i] = NULL;
	}
}

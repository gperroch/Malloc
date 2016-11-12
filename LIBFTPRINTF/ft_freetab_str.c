/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 09:59:52 by gperroch          #+#    #+#             */
/*   Updated: 2016/03/22 11:41:07 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdlib.h>

void	ft_freetab_str(char **tab, int length)
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

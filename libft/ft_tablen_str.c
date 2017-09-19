/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 10:20:15 by gperroch          #+#    #+#             */
/*   Updated: 2016/03/25 12:44:17 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_tablen_str(char **tab)
{
	int	length;
	int	i;

	i = -1;
	length = 0;
	while (tab && tab[++i])
		length++;
	return (length);
}

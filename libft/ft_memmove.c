/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 10:15:04 by gperroch          #+#    #+#             */
/*   Updated: 2016/02/17 10:57:27 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dsttmp;
	char	*srctmp;
	int		i;

	dsttmp = (char*)dst;
	srctmp = (char*)src;
	if (srctmp < dsttmp)
	{
		i = (int)len - 1;
		while (i >= 0)
		{
			dsttmp[i] = srctmp[i];
			i--;
		}
	}
	else if (srctmp != dsttmp)
	{
		i = -1;
		while (++i < (int)len)
			dsttmp[i] = srctmp[i];
	}
	return (dst);
}

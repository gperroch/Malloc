/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 09:53:47 by gperroch          #+#    #+#             */
/*   Updated: 2016/02/17 10:57:39 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char	*s2;

	s2 = (unsigned char*)s;
	while (len--)
		*s2++ = (unsigned char)c;
	return (s);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 10:37:49 by gperroch          #+#    #+#             */
/*   Updated: 2016/02/17 11:32:45 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	char *tmp;

	tmp = dst;
	while (n > 0 && *src != '\0')
	{
		*tmp++ = *src++;
		--n;
	}
	while (n > 0)
	{
		*tmp++ = '\0';
		--n;
	}
	return (dst);
}

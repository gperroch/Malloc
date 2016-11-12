/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 09:18:23 by gperroch          #+#    #+#             */
/*   Updated: 2016/02/17 11:34:17 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libftprintf.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*copie;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (!(copie = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	while (i < (int)len)
	{
		copie[i] = (char)s[start + i];
		i++;
	}
	copie[i] = '\0';
	return (copie);
}

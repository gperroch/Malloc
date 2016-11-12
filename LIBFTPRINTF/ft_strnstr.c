/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 11:19:33 by gperroch          #+#    #+#             */
/*   Updated: 2016/02/17 11:33:33 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	int i;
	int j;

	i = 0;
	if (s2[0] == '\0')
		return ((char*)s1);
	while (s1[i] != '\0' && i < (int)n)
	{
		if (s1[i] == s2[0])
		{
			j = 0;
			while ((i + j) < (int)n && s1[i + j] == s2[j] && s2[j] != '\0')
				j++;
			if (s2[j] == '\0')
				return ((char*)&s1[i]);
		}
		i++;
	}
	return (0);
}

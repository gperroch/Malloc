/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 09:12:01 by gperroch          #+#    #+#             */
/*   Updated: 2016/02/17 11:31:09 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libftprintf.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;
	int		l1;
	int		l2;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	l1 = (int)ft_strlen((char*)s1);
	l2 = (int)ft_strlen((char*)s2);
	if (!(s3 = (char*)malloc(sizeof(char) * (l1 + l2 + 1))))
		return (0);
	while (i < (l1 + l2))
	{
		if (i < l1)
			s3[i] = (char)s1[i];
		else
			s3[i] = (char)s2[i - l1];
		i++;
	}
	s3[i] = '\0';
	return (s3);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 10:31:51 by gperroch          #+#    #+#             */
/*   Updated: 2016/02/17 11:30:09 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libftprintf.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;

	i = ft_strlen(s1);
	if (!(s2 = (char*)malloc(sizeof(char) * (i + 1))) || s1 == NULL)
		return (NULL);
	s2[i] = '\0';
	while (i--)
		s2[i] = s1[i];
	return (s2);
}

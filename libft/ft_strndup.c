/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 15:08:57 by gperroch          #+#    #+#             */
/*   Updated: 2016/02/17 11:32:56 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libftprintf.h"

char		*ft_strndup(const char *str, size_t n)
{
	char	*copy;
	size_t	i;

	i = ft_strlen(str);
	if (n < i)
		i = n;
	if (!(copy = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	copy[i] = '\0';
	while (i--)
		copy[i] = str[i];
	return (copy);
}

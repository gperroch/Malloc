/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 15:04:20 by gperroch          #+#    #+#             */
/*   Updated: 2016/02/17 11:30:18 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libftprintf.h"

char		*ft_strdupchr(const char *str, int c)
{
	char	*copy;
	int		i;

	i = ft_strlenchr(str, c);
	if (!(copy = (char*)malloc(sizeof(char) * (i + 1))) || str == NULL)
		return (NULL);
	copy[i] = '\0';
	while (i--)
		copy[i] = str[i];
	return (copy);
}

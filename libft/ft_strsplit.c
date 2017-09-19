/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 09:17:59 by gperroch          #+#    #+#             */
/*   Updated: 2016/02/17 11:33:55 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libftprintf.h"

static int	strings(char *str, char c)
{
	int		nb;
	int		i;

	i = 0;
	nb = 1;
	while (str[i] != '\0' && str[i] == c)
		i++;
	if (str[i] == '\0')
		nb = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c && str[i + 1] != '\0' && str[i + 1] != c)
			nb++;
		i++;
	}
	return (nb);
}

char		**ft_strsplit(char const *s, char c)
{
	int		nb;
	char	*start;
	char	**result;
	int		i;

	i = -1;
	if (s == NULL || c == 0)
		return (NULL);
	nb = strings((char*)s, c);
	if (!(result = (char**)malloc(sizeof(char*) * (strings((char*)s, c) + 1))))
		return (NULL);
	start = (char*)s;
	while (s[++i] != '\0')
	{
		if (s[i] == c)
		{
			if (start != &s[i])
				*(result++) = ft_strsub(start, 0, &s[i] - start);
			start = (char*)(&s[i] + 1);
		}
	}
	if (start != &s[i])
		*(result++) = ft_strsub(start, 0, &s[i] - start);
	*result = NULL;
	return (result - nb);
}

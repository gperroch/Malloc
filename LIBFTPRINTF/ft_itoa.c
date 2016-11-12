/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 08:59:23 by gperroch          #+#    #+#             */
/*   Updated: 2016/02/17 10:53:15 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdlib.h>

static char	*ft_writing(int n, int o, int i, char *result)
{
	int k;

	k = n;
	result[i] = '\0';
	if (o == 1)
		result[0] = '-';
	while ((i-- > 0 && o == 0) || (i > 0 && o == 1))
	{
		result[i] = (k % 10) + 48;
		k = (k - (k % 10)) / 10;
	}
	return (result);
}

static int	ft_len(int i, int n)
{
	int k;

	k = n;
	while (k != 0)
	{
		k = (k - (k % 10)) / 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	char	*result;
	int		i;
	int		o;

	o = 0;
	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		o = 1;
		n = -n;
		i++;
	}
	if (n == 0)
	{
		if (!(result = (char*)malloc(sizeof(char) * 2)))
			return (NULL);
		result[0] = '0';
		result[1] = '\0';
		return (result);
	}
	if (!(result = (char*)malloc(sizeof(char) * (ft_len(i, n) + 1))))
		return (NULL);
	return (ft_writing(n, o, ft_len(i, n), result));
}

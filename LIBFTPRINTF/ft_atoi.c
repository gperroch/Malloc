/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 11:33:45 by gperroch          #+#    #+#             */
/*   Updated: 2016/02/17 10:51:26 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_atoi(const char *str)
{
	int i;
	int sign;
	int nb;

	i = 0;
	sign = 0;
	nb = 0;
	while (str[i] != 0 && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
				str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] == '-')
	{
		nb = -nb;
		sign = 1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	i--;
	while (str[++i] != '\0' && ft_isdigit(str[i]))
		nb = nb * 10 + str[i] - '0';
	if (sign == 1)
		nb *= -1;
	return (nb);
}

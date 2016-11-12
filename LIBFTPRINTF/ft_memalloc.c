/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 09:01:58 by gperroch          #+#    #+#             */
/*   Updated: 2016/02/17 10:55:31 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void	*tmp;

	if (!(tmp = (void*)malloc(sizeof(void) * size)))
		return (0);
	ft_bzero(tmp, size);
	return (tmp);
}

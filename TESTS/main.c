/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 11:28:50 by gperroch          #+#    #+#             */
/*   Updated: 2017/03/29 11:39:55 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int			main(int argc, char **argv)
{
	char	*ptr1;

	ptr1 = (char*)malloc(sizeof(char) * 10);
	ptr1[9] = 0;
	ft_memset(ptr1, 65, 9);
	write(1, ptr1, 9);
	write(1, "\n", 1);
	free(ptr1 + 3);
	ft_memset(ptr1, 66, 3);
	write(1, ptr1, 9);
	write(1, "\n", 1);
	return 0;
}

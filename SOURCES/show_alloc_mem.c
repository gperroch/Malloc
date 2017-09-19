/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 14:52:45 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/19 11:39:10 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void				show_alloc_mem(void)
{
	t_metadata		*bloc;
	t_metadata		*area;

	area = g_start;
	while (area && area->magic_number == MAGIC_NUMBER_AREA)
	{
		bloc = (t_metadata*)((char*)area + sizeof(t_metadata));
		if (area->size_data == TINY)
			ft_print_area("TINY : ", bloc);
		else if (area->size_data == SMALL)
			ft_print_area("SMALL : ", bloc);
		else
			ft_print_area("LARGE : ", bloc);
		while (bloc && bloc->magic_number == MAGIC_NUMBER_BLOC)
		{
			if (!bloc->free)
				ft_print_bloc(bloc);
			bloc = bloc->next;
		}
		area = area->next;
	}
}

static void			ft_display_addr(void *ptr)
{
	int				i;
	uintmax_t		rem;
	uintmax_t		num;
	char			str[9];
	int				base;

	num = ft_address(ptr);
	base = 16;
	i = 0;
	rem = num;
	ft_memset(&str, '0', 10);
	if (num == 0)
		write(1, "0", 1);
	if (num == 0)
		return ;
	while ((rem = rem / base) != 0)
		i++;
	while (num != 0)
	{
		rem = num % base;
		str[i--] = (rem > 9) ? (rem - 10) + 'A' : rem + '0';
		num = num / base;
	}
	write(1, "0x", 2);
	write(1, &str, 9);
}

static uintmax_t	ft_address(void *ptr)
{
	uintmax_t		mask;
	uintmax_t		num;
	int				i;

	i = -1;
	mask = 1;
	num = 0;
	while (++i < 64)
	{
		if (mask & (uintmax_t)ptr)
			num |= mask;
		mask = mask << 1;
	}
	return (num);
}

static void			ft_print_area(char *str, t_metadata *bloc)
{
	ft_putstr(str);
	ft_display_addr(bloc);
	ft_putstr("\n");
}

static void			ft_print_bloc(t_metadata *bloc)
{
	ft_display_addr((char*)bloc + sizeof(t_metadata));
	ft_putstr(" - ");
	ft_display_addr((char*)bloc + sizeof(t_metadata) + bloc->size_total);
	ft_putstr(" : ");
	ft_putunbr(bloc->size_total);
	ft_putstr(" octets\n");
}

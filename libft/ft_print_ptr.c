/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 16:18:52 by gperroch          #+#    #+#             */
/*   Updated: 2016/03/13 13:00:41 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static intmax_t		ft_address(void *ptr)
{
	intmax_t		mask;
	intmax_t		num;
	int				i;

	i = -1;
	mask = 1;
	num = 0;
	while (++i < 64)
	{
		if (mask & (intmax_t)ptr)
			num |= mask;
		mask = mask << 1;
	}
	return (num);
}

static char			*ft_string_wchar(void *ptr, int *size_s)
{
	char			*regex_printed;
	char			*tmp;
	int				len;
	int				i;

	len = -1;
	i = -1;
	regex_printed = ft_strnew(1);
	while (((int*)ptr)[++len])
	{
		if (ft_strlen(ft_itoabase(((int*)ptr)[len], 2)) > 7)
			*size_s = 2;
		if (ft_strlen(ft_itoabase(((int*)ptr)[len], 2)) > 11)
			*size_s = 3;
		if (ft_strlen(ft_itoabase(((int*)ptr)[len], 2)) > 16)
			*size_s = 4;
	}
	while (++i < len)
	{
		tmp = ft_strjoin(regex_printed, ft_wchar_display(((int*)ptr)[i]));
		free(regex_printed);
		regex_printed = ft_strdup(tmp);
		free(tmp);
	}
	return (regex_printed);
}

char				*ft_print_ptr(char *convchars, va_list ap, int *size_s)
{
	void			*ptr;
	char			*tmp;
	char			*regex_printed;

	tmp = "";
	if (!(regex_printed = ft_strnew(0)))
		return (NULL);
	if (!(tmp = ft_strnew(0)))
		return (NULL);
	ptr = va_arg(ap, void*);
	if (convchars[0] == 's' && !ptr)
		return (ft_strdup("(null)"));
	if (convchars[0] == 's' && !convchars[1])
		return ((regex_printed = ft_strdup((char*)ptr)));
	if (convchars[0] == 's' && convchars[1] == 'l')
		return (ft_string_wchar(ptr, size_s));
	if (convchars[0] == 'p')
		return (ft_strjoin("0x", ft_itoabase(ft_address(ptr), 16)));
	return (NULL);
}

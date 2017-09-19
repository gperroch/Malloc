/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_integers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 12:20:06 by gperroch          #+#    #+#             */
/*   Updated: 2016/03/13 13:14:50 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void			ft_up(char *str)
{
	int				i;

	i = -1;
	while (str[++i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
	}
}

static char			*ft_signed_int(intmax_t arg, char *convchars, char *regex)
{
	if (regex || (convchars[0] != 'i' && convchars[0] != 'd'))
		return (regex);
	if (!convchars[1])
		return (ft_itoabase((int)arg, 10));
	if (convchars[1] == 'l' && !convchars[2])
		return (ft_itoabase((long int)arg, 10));
	if (convchars[1] == 'l' && convchars[2] == 'l')
		return (ft_itoabase((long long int)arg, 10));
	if (convchars[1] == 'h' && !convchars[2])
		return (ft_itoabase((short)arg, 10));
	if (convchars[1] == 'h' && convchars[2] == 'h')
		return (ft_itoabase((signed char)arg, 10));
	if (convchars[1] == 'j' && !convchars[2])
		return (ft_itoabase(arg, 10));
	if (convchars[1] == 'z' && !convchars[2])
		return (ft_itoabase((size_t)arg, 10));
	return (NULL);
}

static char			*ft_unsigned_int(intmax_t arg, char *convchars,
		int base, char *regex)
{
	if (regex || (convchars[0] != 'o' && convchars[0] != 'u'
				&& convchars[0] != 'x' && convchars[0] != 'X'))
		return (regex);
	if (!convchars[1])
		return (ft_itoabase_unsigned((unsigned int)arg, base));
	else if (convchars[1] == 'l' && !convchars[2])
		return (ft_itoabase_unsigned((unsigned long)arg, base));
	else if (convchars[1] == 'l' && convchars[2] == 'l')
		return (ft_itoabase_unsigned((unsigned long long)arg, base));
	else if (convchars[1] == 'h' && !convchars[2])
		return (ft_itoabase_unsigned((unsigned short)arg, base));
	else if (convchars[1] == 'h' && convchars[2] == 'h')
		return (ft_itoabase_unsigned((unsigned char)arg, base));
	else if (convchars[1] == 'j' && !convchars[2])
		return (ft_itoabase_unsigned((uintmax_t)arg, base));
	else if (convchars[1] == 'z' && !convchars[2])
		return (ft_itoabase_unsigned((size_t)arg, base));
	return (NULL);
}

static char			*ft_particular(intmax_t arg, char *convchars, char *regex)
{
	char			*regex_printed;

	if (regex || (convchars[0] != 'd' && convchars[0] != 'i'))
		return (regex);
	regex_printed = regex;
	if (arg == 9223372036854775807 && (convchars[0] == 'd'
				|| convchars[0] == 'i')
			&& convchars[1] == 'l' && convchars[2] == 'l')
		regex_printed = ft_strdup("9223372036854775807");
	else if ((arg + 1) == -9223372036854775807 && (convchars[0] == 'd'
				|| convchars[0] == 'i') && convchars[1] == 'l'
			&& (convchars[2] == 'l' || !convchars[2]))
		regex_printed = ft_strdup("-9223372036854775808");
	else if ((arg + 1) == -9223372036854775807 && (convchars[0] == 'd'
				|| convchars[0] == 'i') && (convchars[1] == 'j'
					|| convchars[1] == 'z') && !convchars[2])
		regex_printed = ft_strdup("-9223372036854775808");
	return (regex_printed);
}

char				*ft_print_integers(char *convchars, va_list ap)
{
	intmax_t		arg;
	char			*regex_printed;
	int				base;

	base = 10;
	if (ft_wrong_specifier(convchars[0]))
		return (ft_memset(ft_strnew(1), convchars[0], 1));
	if (convchars[0] == 'o')
		base = 8;
	else if (convchars[0] == 'x' || convchars[0] == 'X')
		base = 16;
	if (convchars[0] == '%')
		return (ft_memset(ft_strnew(1), '%', 1));
	arg = va_arg(ap, intmax_t);
	regex_printed = NULL;
	regex_printed = ft_particular(arg, convchars, regex_printed);
	regex_printed = ft_signed_int(arg, convchars, regex_printed);
	regex_printed = ft_unsigned_int(arg, convchars, base, regex_printed);
	if (convchars[0] == 'c' && !convchars[1])
		regex_printed = ft_memset(ft_strnew(1), (int)arg, 1);
	else if (convchars[0] == 'c' && convchars[1] == 'l')
		regex_printed = ft_wchar_display(arg);
	if (convchars[0] == 'X')
		ft_up(regex_printed);
	return (regex_printed);
}

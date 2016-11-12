/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 13:41:36 by gperroch          #+#    #+#             */
/*   Updated: 2016/03/13 14:21:03 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_calcul(char *format, char spec, int *precision)
{
	while (*format != spec)
		format++;
	while (*(--format) != '.' && *format != '%')
		;
	if (*format != '.' || spec == '%' || spec == 'c'
			|| spec == 'C')
		return (0);
	*precision = ft_atoi(&format[1]);
	return (1);
}

static void	ft_auxi(int precision, char **regex_printed, char spec, char **tmp)
{
	if (!precision && ft_strlen(*regex_printed) == 1
			&& (*regex_printed)[0] == '0' && spec != 'c'
			&& spec != 'C' && spec != 's' && spec != 'S')
	{
		free(*regex_printed);
		*regex_printed = ft_strdup("");
	}
	else if (!precision && ft_strlen(*regex_printed) == 3
			&& !ft_strcmp(*regex_printed, "0x0") && spec == 'p')
	{
		free(*regex_printed);
		*regex_printed = ft_strdup("0x");
	}
	if ((precision + 3) > (int)ft_strlen(*regex_printed) && spec == 'p')
	{
		*tmp = ft_strdup(&(*regex_printed)[2]);
		free(*regex_printed);
		*regex_printed =
			ft_strjoin(ft_memset(ft_strnew(precision - ft_strlen(*tmp)),
						'0', (precision - ft_strlen(*tmp))), *tmp);
		free(*tmp);
		*tmp = ft_strdup(*regex_printed);
		*regex_printed = ft_strjoin("0x", *tmp);
		free(*tmp);
	}
}

int			ft_precision(char *format, char **regex_printed, char spec,
		int size_s)
{
	int		preci;
	char	*tmp;
	int		len;

	len = (int)ft_strlen(*regex_printed);
	tmp = NULL;
	if (!ft_calcul(format, spec, &preci))
		return (0);
	if ((spec == 's') && preci < len)
		tmp = ft_strncpy(ft_strnew(preci), *regex_printed, preci);
	if ((spec == 'S') && preci < len)
		(*regex_printed)[preci - (preci % size_s)] = 0;
	((*regex_printed)[0] == '-' && preci > len - 1) ? (len--) : (0);
	if (spec != 's' && spec != 'S' && spec != 'c' && spec != 'p' && preci > len)
		tmp = ft_strjoin(ft_memset(ft_strnew(preci - len),
					'0', (preci - len)), *regex_printed);
	if (tmp)
	{
		(tmp[preci - len] == '-' && preci >= len) ? (tmp[0] = '-') : 0;
		(tmp[preci - len] == '-' && preci >= len) ? (tmp[preci - len] = 48) : 0;
		free(*regex_printed);
		*regex_printed = tmp;
	}
	ft_auxi(preci, regex_printed, spec, &tmp);
	return ((preci == 0) ? (preci = -1) : (preci));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modif_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 10:16:50 by gperroch          #+#    #+#             */
/*   Updated: 2016/03/13 13:15:56 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void		ft_flag_zero(char **regex_printed, char specifier)
{
	int			i;

	i = -1;
	while ((*regex_printed)[++i] == ' ')
		(*regex_printed)[i] = '0';
	if (specifier == 'p' && !ft_strcmp(&(*regex_printed)[i], "0x0"))
		*regex_printed = ft_strjoin(&(*regex_printed)[i],
				ft_memset(ft_strnew(i + 1), '0', i));
	((*regex_printed)[i] == '-' && i > 0) ? ((*regex_printed)[0] = '-') : (0);
	((*regex_printed)[i] == '-' && i > 0) ? ((*regex_printed)[i] = '0') : (0);
}

static void		ft_flag_diese(char **regex_printed,
		char specifier, char *format)
{
	char		*tmp;
	char		*add;
	int			i;
	int			zero;

	tmp = *regex_printed;
	i = 0;
	zero = 0;
	if (!**regex_printed && (specifier == 'x' || specifier == 'X'))
		return ;
	((*regex_printed)[0] == '0' && !(*regex_printed)[1]) ? (zero = 1) : (0);
	while ((*regex_printed)[i] == ' ' || ((*regex_printed)[i] == '0' && i < 2))
		i++;
	if (ft_precision(format, regex_printed, specifier, 0) > 0)
		i = 0;
	if (specifier == 'x' && !zero)
		add = ft_strjoin("0x", &(*regex_printed)[i]);
	if (specifier == 'X' && !zero)
		add = ft_strjoin("0X", &(*regex_printed)[i]);
	if ((specifier == 'o' || specifier == 'O') && !zero)
		add = ft_strjoin("0", &(*regex_printed)[i]);
	free(*regex_printed);
	*regex_printed = add;
	ft_fieldwidth(format, regex_printed, specifier);
}

static void		ft_flag_plus(char **regex_printed, char specifier)
{
	int			i;
	char		*add;

	i = 0;
	while ((*regex_printed)[i] == ' ')
		i++;
	if ((*regex_printed)[i] == '-' || specifier == 'c' || specifier == 'C'
			|| specifier == 'o' || specifier == 'O'
			|| specifier == 's' || specifier == 'S'
			|| specifier == 'x' || specifier == 'X' || specifier == 'p')
		return ;
	if ((i > 0 || (*regex_printed)[0] == '0') && (*regex_printed)[1]
			&& (*regex_printed)[0] == '0')
		(*regex_printed)[0] = '+';
	else if ((i > 0 || (*regex_printed)[0] == '0') && (*regex_printed)[1]
			&& (*regex_printed)[0] != '0')
		(*regex_printed)[i - 1] = '+';
	else if (i == 0)
	{
		add = ft_strjoin("+", ft_strdup((*regex_printed)));
		free(*regex_printed);
		*regex_printed = ft_strdup(add);
		free(add);
	}
}

static void		ft_flag_moins(char **regex_printed)
{
	char		*add;
	int			i;

	i = 0;
	while ((*regex_printed)[i] == ' ')
		i++;
	if (i > 0)
	{
		add = ft_strjoin(ft_strdup(&(*regex_printed)[i]),
				(char*)ft_memset(ft_strnew(i), ' ', i));
		free(*regex_printed);
		*regex_printed = ft_strdup(add);
		free(add);
	}
}

void			ft_modif_flags(char *format, char **regex_printed,
		char specifier, char *flags)
{
	char		*add;

	if (flags[1])
		ft_flag_zero(regex_printed, specifier);
	if (flags[0])
		ft_flag_diese(regex_printed, specifier, format);
	if (flags[3])
		ft_flag_plus(regex_printed, specifier);
	if (flags[2])
		ft_flag_moins(regex_printed);
	if (flags[4] && (*regex_printed)[0] <= '9' && (*regex_printed)[0] > '0')
	{
		add = ft_strjoin(" ", (*regex_printed));
		free(*regex_printed);
		*regex_printed = add;
		if ((*regex_printed)[ft_strlen(*regex_printed) - 1] == ' ' && flags[2])
			(*regex_printed)[ft_strlen(*regex_printed) - 1] = 0;
	}
	else if (flags[4] && (*regex_printed)[0] == '0')
		(*regex_printed)[0] = ' ';
}

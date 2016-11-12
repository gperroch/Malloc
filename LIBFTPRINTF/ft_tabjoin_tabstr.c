/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabjoin_tabstr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 11:02:50 by gperroch          #+#    #+#             */
/*   Updated: 2016/03/25 12:45:27 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char		**ft_tabjoin_tabstr(char **tab1, int len1, char **tab2, int len2)
{
	int		i;
	char	**new_tab;

	i = -1;
	len1 = (len1 < 0) ? (ft_tablen_str(tab1)) : (len1);
	len2 = (len2 < 0) ? (ft_tablen_str(tab2)) : (len2);
	;
	if (!(new_tab = (char**)malloc(sizeof(char*) * (len1 + len2 + 1))))
		exit(EXIT_FAILURE);
	new_tab[len1 + len2] = NULL;
	while (++i < len1 + len2)
	{
		if (i < len1)
			new_tab[i] = ft_strdup(tab1[i]);
		else
			new_tab[i] = ft_strdup(tab2[i - len1]);
	}
	return (new_tab);
}

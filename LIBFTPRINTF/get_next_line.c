/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 14:46:38 by gperroch          #+#    #+#             */
/*   Updated: 2016/03/16 12:20:35 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libftprintf.h"

int						gnl_reading(char **poubelle, char **buff,
		int *read_ret, int fd)
{
	*read_ret = 1;
	if (!*poubelle)
	{
		if (!(*poubelle = ft_strnew(0)))
			return (-1);
	}
	else if (ft_strlenchr(*poubelle, '\n') != ft_strlen(*poubelle))
		return (0);
	if (!(*buff = (char*)malloc(sizeof(char) * (BUFF_SIZE_GNL + 1))))
		return (-1);
	while ((ft_strlenchr(*buff, '\n') == ft_strlen(*buff)) && *read_ret > 0)
	{
		ft_memset(*buff, 0, BUFF_SIZE_GNL + 1);
		if ((*read_ret = read(fd, *buff, BUFF_SIZE_GNL)) == -1)
			return (-1);
		*poubelle = ft_strjoin(*poubelle, *buff);
	}
	if (**poubelle)
		*read_ret = 1;
	ft_memset(*buff, 0, BUFF_SIZE_GNL + 1);
	free(*buff);
	return (0);
}

int						gnl_attribution(char **line, char **poubelle,
		int read_ret)
{
	int					i;

	i = 0;
	*line = ft_strdupchr(*poubelle, '\n');
	while ((*poubelle)[i] != '\0' && (*poubelle)[i] != '\n')
		i++;
	if ((*poubelle)[i] == '\n')
		i++;
	*poubelle = &(*poubelle)[i];
	if (read_ret || **poubelle)
		return (1);
	return (0);
}

t_list_gnl				*ft_structure(int fd, t_list_gnl **lst)
{
	t_list_gnl			*cursor;
	t_list_gnl			*new;

	cursor = *lst;
	if (cursor)
	{
		while (cursor->fd != fd && cursor->next)
			cursor = cursor->next;
		if (cursor->fd == fd)
			return (cursor);
	}
	if (!(new = (t_list_gnl*)malloc(sizeof(t_list_gnl))))
		return (NULL);
	new->fd = fd;
	new->poubelle = NULL;
	new->next = NULL;
	if (cursor)
		cursor->next = new;
	else
		*lst = new;
	return (new);
}

int						get_next_line(int const fd, char **line)
{
	static t_list_gnl	*lst = NULL;
	t_list_gnl			*tmp;
	char				*buff;
	int					read_ret;

	if (fd < 0 || fd > 256 || fd == 1 || fd == 2 || !line
			|| BUFF_SIZE_GNL < 1 || BUFF_SIZE_GNL > 2147483647)
		return (-1);
	tmp = ft_structure(fd, &lst);
	if (gnl_reading(&(tmp->poubelle), &buff, &read_ret, fd) == -1)
		return (-1);
	return (gnl_attribution(line, &(tmp->poubelle), read_ret));
}

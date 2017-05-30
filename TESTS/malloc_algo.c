/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 09:58:08 by gperroch          #+#    #+#             */
/*   Updated: 2017/05/30 10:22:20 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#define DEBUG(x) write(1, x, ft_strlen(x));

void            *malloc(size_t size)
{
    static void *start;
    t_area      *area;
    t_block     *bloc;

    start = NULL;
    area = NULL;
    bloc = NULL;
    if (ft_find_area(start, &area, size))
    {
        if (ft_find_bloc(area, &bloc, size))
            ft_update_metadata(bloc, size);
        else if (ft_size_available(area, bloc, size))
            ft_update_new_bloc(bloc, size);
        else
            ft_new_area();
    }
    else
    {
        ft_new_area();
    }

    return (bloc);
}

int         ft_find_area(void *start, t_area **area, size_t size)
{
    t_area  *cursor;

    cursor = start;
    while ((cursor->size_data < size || !cursor->free) && cursor->next)
		cursor = cursor->next;

    *area = cursor;
    if (cursor->size_data >= size && cursor->free)
        return (1);
	return (0);
}

int         ft_find_bloc(t_area *area, t_block **bloc, size_t size) // Mutualiser ft_find_bloc et ft_find_area quand bloc et area auront la meme structure
{
    t_block *cursor;

    cursor = area + sizeof(t_area);
    while ((cursor->size < size || !cursor->free) && cursor->next)
        cursor = cursor->next;

    *bloc = cursor;
    if (cursor->size >= size && cursor->free)
        return (1);
    return (0);
}

int         ft_update_metadata(t_block *bloc, size_t size)
{
    bloc->free = 0;
    bloc->size = size;
    bloc->next = bloc + size;
    return (0);
}

int         ft_size_available(t_area *area, t_block *bloc, size_t size)
{
    if ((unsigned int)bloc + sizeof(t_block) + size <= (unsigned int)area + sizeof(t_area) + area->size_area)
        return (1);
    return (0);
}

int         ft_update_new_bloc(t_block *bloc, size)
{

}

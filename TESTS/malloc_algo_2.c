/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_algo_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 09:58:08 by gperroch          #+#    #+#             */
/*   Updated: 2017/05/30 10:41:15 by gperroch         ###   ########.fr       */
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
    if (!ft_find_area(start, &area, size)) // Pas de zone disponibles trouvée.
    {
        ft_new_area(&area); // Création de la nouvelle zone, ajout du premier bloc vierge.
    }

    ft_find_bloc(area, &bloc, size); // Le bloc est necessairement trouvé. Ajout des cas d'erreur à faire.
    ft_update_metadata(bloc, size); // Cas d'erreurs à faire.
    ft_add_next_metadata(bloc, area); // Ajout des metadata vierges qui font que le bloc est nécessairement trouvé si la zone et validée.Si la zone n'a plus de place, aucune metadata n'est ajoutée et une nouvelle zone sera créée.

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

int         ft_new_area(t_area **area, size_t size) // Ajout d'une nouvelle zone, soit en première position, soit après la dernière zone trouvée.
{
    void    *cursor;
    t_area  *new_area;
    int     size_area;
    t_block first_bloc;

    size_area = (size <= TINY) ? AREA_TINY : AREA_SMALL;
    size_area = (size > TINY && size <= SMALL) ? AREA_SMALL : size_area;
    size_area = (size > SMALL) ? (size + sizeof(t_area) + sizeof(t_block)) : size_area;

    new_area = NULL;
    new_area = mmap(ptr, size_area, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (*area) // Zone non NULL, pas la première utilisation.
    {
        (*area)->next = new_area;
        *area = new_area;
    }

    // Puis ajout du premier bloc vierge.
    first_bloc = ft_memset(&first_bloc, 0, sizeof(t_block));
    cursor = new_area + sizeof(t_area);
    *cursor = first_bloc;
    return (1);
}

int			ft_add_next_metadata()
{
	
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_algo_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 09:58:08 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/02 18:33:56 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#define DEBUG(x) write(1, x, ft_strlen(x));

int         ft_find_area(void *start, t_metadata **area, size_t size);
int         ft_find_bloc(t_metadata *area, t_metadata **bloc, size_t size);
int         ft_update_metadata(t_metadata *bloc, size_t size);
int         ft_size_available(t_metadata *area, t_metadata *bloc, size_t size);
int         ft_new_area(t_metadata **area, size_t size);
int			ft_add_next_metadata(t_metadata *bloc, t_metadata *area);

void            *malloc(size_t size)
{
    static void *start = NULL;
    t_metadata  *area;
    t_metadata  *bloc;
    int         i = 3;

    area = NULL;
    bloc = NULL;
    if (!ft_find_area(start, &area, size)) // Pas de zone disponibles trouvée.
    {
        ft_new_area(&area, size); // Création de la nouvelle zone, ajout du premier bloc vierge.
        if (!start) // Premiere allocation, start est NULL, start devient le debut de la premiere zone.
            start = area;
    }
    i = ft_find_bloc(area, &bloc, size); // Le bloc est necessairement trouvé. Ajout des cas d'erreur à faire.
    //printf("i = %d\n", i);
    ft_update_metadata(bloc, size); // Cas d'erreurs à faire.
    ft_add_next_metadata(bloc, area); // Ajout des metadata qui font que le bloc est nécessairement trouvé si la zone et validée.Si la zone n'a plus de place, aucune metadata n'est ajoutée et une nouvelle zone sera créée.
                                        // ZONE PLEINE : passer le free de la zone a 1. Une nouvelle zone sera creee lors du prochain appel.

    //dump_mem(start, 64 * 30, 32);
    return ((void*)bloc + sizeof(t_metadata));
}

int         ft_find_area(void *start, t_metadata **area, size_t size)
{
    t_metadata  *cursor;

    cursor = (void*)start;
    if (!start)
        return (0);
    //while ((cursor->size_total < size || !cursor->free) && cursor->next)
    while ((cursor->size_data < size || !cursor->free) && cursor->next)
		cursor = cursor->next;

    *area = cursor;
    //if (cursor->size_total >= size && cursor->free )
    if (cursor->size_data >= size && cursor->free )
        return (1);
	return (0);
}

int         ft_find_bloc(t_metadata *area, t_metadata **bloc, size_t size) // Mutualiser ft_find_bloc et ft_find_area quand bloc et area auront la meme structure
{
    t_metadata *cursor;

    cursor = (void*)area + sizeof(t_metadata);
    while ((cursor->size_total < size || !cursor->free) && cursor->next)
        cursor = cursor->next;

    *bloc = cursor;
    if (cursor->size_total >= size && cursor->free)
        return (1);
    return (0);
}

int         ft_update_metadata(t_metadata *bloc, size_t size)
{
    bloc->free = 0;
    bloc->size_total = size;
    bloc->next = bloc + size;
    return (0);
}

int         ft_size_available(t_metadata *area, t_metadata *bloc, size_t size)
{
    if ((unsigned int)bloc + sizeof(t_metadata) + size <= (unsigned int)area + sizeof(t_metadata) + area->size_total)
        return (1);
    return (0);
}

int         ft_new_area(t_metadata **area, size_t size) // Ajout d'une nouvelle zone, soit en première position, soit après la dernière zone trouvée.
{
    char        *cursor;
    t_metadata  *new_area;
    t_metadata  *tmp;
    int         size_total;
    t_metadata  first_bloc;

    size_total = (size <= TINY) ? AREA_TINY : AREA_SMALL;
    size_total = (size > TINY && size <= SMALL) ? AREA_SMALL : size_total;
    size_total = (size > SMALL) ? (size + sizeof(t_metadata) + sizeof(t_metadata)) : size_total;

    new_area = NULL;
    //new_area = mmap(area, size_total, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1, 0);
    new_area = mmap(NULL, size_total, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (*area) // Zone non NULL, pas la première utilisation.
    {
        tmp = *area;
        while (tmp->next)
            tmp = tmp->next;
        //(*area)->next = new_area;
        tmp->next = new_area;
        //*area = new_area;
    }
    *area = new_area;

    new_area->size_total = size_total;
    new_area->size_data = (size <= TINY) ? TINY : SMALL;
    new_area->size_data = (size > SMALL) ? size : new_area->size_data;
    new_area->free = 1;

    // Puis ajout du premier bloc vierge.
    ft_memset(&first_bloc, 0, sizeof(t_metadata));
    cursor = (char*)((char*)new_area + sizeof(t_metadata));
    *((t_metadata*)cursor) = first_bloc;

    printf("NOUVELLE ZONE : %10p %5d %5d\n", new_area, new_area->size_total, new_area->size_data);
    return (1);
}

int			ft_add_next_metadata(t_metadata *bloc, t_metadata *area)
{
    t_metadata  *new_bloc;

    // Le nouveau bloc est a l'address du bloc cense suivre celui en parametre. Prendre en compte la limite de la zone.
    // Il contient free = 1 et la quantite max de donnees qu'il peut recevoir (en fonction de sa zone). La quantité max de donnees (size_data) restera fixe, la quantité effective de donnees sera egale a la max tant que
    // le bloc est free, puis sera changee pour correspondre a la quantite de donnees requise lors de l'allocation. !! MODIFIER LES VARIABLES SIZE_TOTAL ET SIZE_DATA POUR LES RENDRE PLUS PARLANTES.
    new_bloc = (void*)bloc + sizeof(t_metadata) + bloc->size_total;

    if ((char*)new_bloc > (((char*)area + area->size_total) - (area->size_data +sizeof(t_metadata)))) // La zone n'a pas suffisament de place pour un nouveau bloc.
    {
        area->free = 0;
        return (0);
    }

    new_bloc->free = 1;
    new_bloc->size_data = area->size_data;
    bloc->next = new_bloc;
    return (1);
}

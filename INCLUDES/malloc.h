/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 15:05:50 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/19 12:31:59 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/mman.h>
# include "libftprintf.h"
# define TINY 128
# define SMALL 1024
# define SIZE_METADATA sizeof(t_metadata)
# define AREA_TINY (((TINY + SIZE_METADATA) * 106) + SIZE_METADATA + 64)		// Utiliser getpagesize() pour avoir le 4096 => l'ajouter dans la formule
# define AREA_SMALL (((SMALL + SIZE_METADATA) * 101) + SIZE_METADATA + 640)
# define MAGIC_NUMBER_BLOC 0x810C
# define MAGIC_NUMBER_AREA 0x811C

/*
** size_total - 	BLOC : correspond a la taille effective du bloc.
**					AREA : correspond a la taille totale de la zone.
** prev_area  - 	BLOC : adresse de la zone correspondante.
**					AREA : adresse de la zone precedente.
** size_data  - 	BLOC : correspond a la taille maximum du bloc.
**					AREA : comme pour les BLOC.
*/

extern void				*g_start;
typedef struct			s_metadata
{
	size_t				size_total;
	struct s_metadata	*next;
	struct s_metadata	*prev_area;
	int					magic_number;
	int					free;
	size_t				size_data;
	char				padding[24];
}						t_metadata;
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);
void					dump_mem(void *ptr, int len, int col, char *name);
void					show_alloc_mem(void);
void					free(void *ptr);
int						ft_find_area(void *start, t_metadata **area,
	size_t size);
int						ft_find_bloc(t_metadata *area, t_metadata **bloc,
	size_t size);
int						ft_update_metadata(t_metadata *bloc, size_t size);
int						ft_size_available(t_metadata *area, t_metadata *bloc,
	size_t size);
int						ft_new_area(t_metadata *start, t_metadata **area,
	size_t size);
int						ft_add_next_metadata(t_metadata *bloc,
	t_metadata *area);
int						ft_find_bloc_area(t_metadata *area, t_metadata **target,
	size_t size, int bloc);
void					ft_area_free(t_metadata *area);
void					ft_print_area(char *str, t_metadata *bloc);
uintmax_t				ft_address(void *ptr);
void					ft_display_addr(void *ptr);
void					ft_print_bloc(t_metadata *bloc);
void					ft_init_first_bloc(t_metadata *first_bloc,
	t_metadata *new_area);
int						ft_new_area(t_metadata *start, t_metadata **area,
	size_t size);
void					ft_init_new_area(t_metadata *new_area,
	size_t size_total, size_t size);
void					ft_add_to_last_area(t_metadata *start,
	t_metadata *new_area);
int						ft_add_extra_bloc(void *ptr, size_t size,
	size_t size_total,	t_metadata *bloc);
int						ft_calcul_size_available(t_metadata **next_bloc,
	size_t *size_total, size_t size, t_metadata *bloc);
void					*ft_new_allocation(void *ptr, size_t size);

#endif

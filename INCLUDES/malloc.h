/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 15:05:50 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/11 15:32:20 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/mman.h>
# include "libftprintf.h"
# define TINY 128 //64
# define SMALL 1024
# define AREA_TINY (((TINY + sizeof(t_block)) * 128) - 32)
# define AREA_SMALL (((SMALL + sizeof(t_block)) * 128) - 32)// + sizeof(t_area))
# define align4(x) ((((x - 1) >> 2) << 2) + 4)
# define MAGIC_NUMBER_BLOC 0x810C
# define MAGIC_NUMBER_AREA 0x811C

typedef struct		s_block  // Verifier la taille maximum de la structure en assignant la valeur maximum aux variables numériques
{
	size_t			size;
	struct s_block	*next;
	int				free;
	char			data[8];
}					t_block;

typedef struct		s_area // N'AVOIR PLUS QU'UNE SEULE STRUCTURE POUR AREA ET BLOCK
{
	//Taille de la zone complete
	size_t			size_area;
	struct s_area	*next;
	int				free;
	//Taille des donnees (zone - structure d'entete)
	size_t			size_data;
}					t_area;

typedef struct			s_metadata // size_?? a remanier.
{
	size_t				size_total; // BLOC : correspond a la taille effective du bloc. // AREA : correspond a la taille totale de la zone.
	struct s_metadata	*next;
	struct s_metadata	*prev_area; // BLOC : adresse de la zone correspondante. // AREA : adresse de la zone precedente.
	int					magic_number;
	int					free;
	size_t				size_data; // BLOC : correspond a la taille maximum du bloc. // AREA : comme pour les BLOC.
	char				padding[16];
}						t_metadata;

void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				dump_mem(void *ptr, int len, int col);
void				show_alloc_mem(void);
void				free(void *ptr);
int					ft_new_metadata(void *addr_block, int size, t_area *t_area);
static t_area	*ft_find_next_suitable_area(t_area *area, size_t size);
static t_block	*ft_find_next_suitable_block(t_area *area, size_t size);
static t_area	*ft_map_new_area(t_area *area,size_t size);
static t_area	*ft_mapping(void *ptr, size_t size);



#endif

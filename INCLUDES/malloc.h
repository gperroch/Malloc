/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 15:05:50 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/02 15:09:35 by gperroch         ###   ########.fr       */
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
# define SMALL 2048
# define AREA_TINY (((TINY + sizeof(t_block)) * 100) + sizeof(t_area))
# define AREA_SMALL (((SMALL + sizeof(t_block)) * 100) + sizeof(t_area))
# define align4(x) ((((x - 1) >> 2) << 2) + 4)

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

typedef struct			s_metadata
{
	size_t				size_total; // Visiblement, dans le cas d'un bloc, cela correspond a la taille du bloc.
	struct s_metadata	*next;
	int					free;
	size_t				size_data;
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

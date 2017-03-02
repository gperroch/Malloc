/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 15:05:50 by gperroch          #+#    #+#             */
/*   Updated: 2016/05/18 15:48:50 by gperroch         ###   ########.fr       */
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

typedef struct		s_block
{
	size_t			size;
	struct s_block	*next;
	int				free;
	char			data[8];
}					t_block;

typedef struct		s_area
{
	//Taille de la zone complete
	size_t			size_area;
	struct s_area	*next;
	int				free;
	//Taille des donnees (zone - structure d'entete)
	size_t			size_data;
}					t_area;

void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				dump_mem(void *ptr, int len);
void				show_alloc_mem(void);
void				free(void *ptr);
int					ft_new_metadata(void *addr_block, int size);
static t_area	*ft_find_next_suitable_area(t_area *area, size_t size);
static t_block	*ft_find_next_suitable_block(t_area *area, size_t size);
static t_area	*ft_map_new_area(t_area *area,size_t size);



#endif

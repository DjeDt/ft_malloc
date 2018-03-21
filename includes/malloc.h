/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:41:23 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/21 19:11:44 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		MALLOC_H
# define	MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <pthread.h>

# include "../libft/includes/libft.h"
# include "../ft_printf/includes/printf.h"

typedef struct		s_chunk
{
	size_t			size;			/* size of current data chunk */
	void			*data;
	int				statut;			/* is available ? */
//	size_t			safe;			/* to check if data does not differ */
	struct s_chunk	*next;
	struct s_chunk	*prev;
}					t_chunk;

typedef struct		s_area
{
	size_t			size_used;
	size_t			size_max;
	void			*map;
	t_chunk			*chunk;
	struct s_area	*next;
}					t_area;

typedef	struct		s_pages
{
	t_area			*small;
	t_area			*medium;
	t_area			*large;
	t_chunk			*bin;		/* used to track freed chunk */

}					t_pages;

# define		SUCCESS	1
# define		NOPE	0
# define		ERROR	-1

# define		FREE	1
# define		USED	0

# define		TINY_SIZE	128
# define		MEDIUM_SIZE	512

# define		AREA_SIZE	sizeof(t_area)
# define		HEADER_SIZE	sizeof(t_chunk)

t_pages				g_page;
pthread_mutex_t		g_thread;

/*
**	malloc func
*/
void	*malloc(size_t size);

void	*push_chunk_to_area(size_t size);
t_area	*create_new_area(size_t size, t_area *prev);
t_area	*create_large_area(size_t size);

t_area	*search_small_area(size_t size);
t_area	*search_medium_area(size_t size);
void	*search_free_chunk(t_area *area, size_t size);

/*
**	free func
*/
void	free(void *ptr);

/*
**	realloc func
*/
void	*realloc(void *ptr, size_t size);

void	count_zone(t_area **area);
void	print_all(t_chunk **chunk);
void	ft_putaddr(void *ptr);

#endif










/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:41:23 by ddinaut           #+#    #+#             */
/*   Updated: 2018/04/16 17:05:01 by ddinaut          ###   ########.fr       */
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
	int				statut;			/* is available ? */
	size_t			size;			/* size of current data chunk */
	struct s_chunk	*next;
}					t_chunk;

typedef struct		s_area
{
	size_t			size_used;
	size_t			size_max;
	t_chunk			*chunk;
	struct s_area	*next;
}					t_area;

typedef	struct		s_pages
{
	t_area			*small;
	t_area			*medium;
	t_area			*large;
}					t_pages;

# define		ALIGN_MOD(x) ((x % 16) || !x) ? (x + 16) - (x % 16) : x
# define		ALIGN(x) ALIGN_MOD((x))

# define		SUCCESS	1
# define		NOPE	0
# define		ERROR	-1

# define		FREE	1
# define		USED	0

# define		TINY_SIZE	128
# define		MEDIUM_SIZE	512

# define		AREA_SIZE	sizeof(t_area)
# define		HEADER_SIZE	sizeof(t_chunk)


/* Debug values */
#define DEBUG 1
static size_t hmt;

t_pages				g_page;
pthread_mutex_t		g_thread;

/*
**	malloc func
*/
void	*malloc(size_t size);

void	*push_chunk_to_area(size_t size);
t_area	*create_new_area(size_t size, t_area *prev);
t_area	*create_large_area(size_t size);


/*
t_area	*search_small_area(size_t size);
t_area	*search_medium_area(size_t size);
*/
t_area	*search_small_area(size_t size, t_area **area);
t_area	*search_medium_area(size_t size, t_area **area);

void	*search_free_chunk(t_area *area, size_t size);

/*
**	free func
*/
void	free(void *ptr);

/*
**	realloc func
*/
void	*realloc(void *ptr, size_t size);

/* need to sup */

void	count_zone(t_area **area);
void	print_all(t_chunk **chunk);
void	ft_putaddr(void *ptr);
void	print_large(void);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:41:23 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/07 20:24:33 by ddinaut          ###   ########.fr       */
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
	size_t			prev_size;		/* previous chunk size */
	int				statut;			/* is available ? */
//	size_t			safe;			/* to check if data does not differ */
	struct s_chunk	*previous;
	struct s_chunk	*next;
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

# define		FREE	1
# define		USED	0

# define		TINY_SIZE	128
# define		MEDIUM_SIZE	1024

# define		AREA_SIZE	sizeof(t_area)
# define		HEADER_SIZE	sizeof(t_chunk)

t_pages				g_page;
pthread_mutex_t		g_thread;

/*
**	malloc func
*/
void	*malloc(size_t size);

void	*push_to_small_area(size_t size);
void	*push_to_medium_area(size_t size);
void	*push_to_medium_area(size_t size);
void	*push_chunk(size_t size);

/*
**	free func
*/
void	free(void *ptr);

/*
**	utils func
*/
size_t	get_power_of_2(size_t size);
void    print_allocated_chunk(t_chunk **lst);

#endif

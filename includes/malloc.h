/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:41:23 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/06 18:35:26 by ddinaut          ###   ########.fr       */
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
	int				statut;			/* is available ? */
//	size_t			safe;			/* to check if data does not differ */
	struct s_chunk	*next;
}					t_chunk;

typedef	struct		s_pages
{
	t_chunk			*tiny;
	t_chunk			*medium;
	t_chunk			*large;
	struct s_pages	*next;
}					t_pages;

# define		FREE	1
# define		USED	0

# define		TINY_SIZE	100
# define		MEDIUM_SIZE	1000
# define		LARGE_SIZE	10000
# define		HEADER_SIZE	sizeof(t_chunk)

t_pages				g_page;
pthread_mutex_t		g_lock;

/*
**	malloc func
*/
void	*malloc(size_t size);
void	*create_new_pages(size_t size, int page_size);

t_chunk	*create_chunk(size_t size);
t_chunk	*search_free_chunk(size_t size, t_chunk **list);

void	*add_to_tiny(size_t size, t_chunk **zone);
void	*add_to_medium(size_t size, t_chunk **zone);
void	*add_to_large(size_t size, t_chunk **zone);

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

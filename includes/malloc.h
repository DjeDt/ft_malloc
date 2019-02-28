/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:41:23 by ddinaut           #+#    #+#             */
/*   Updated: 2019/02/28 17:48:25 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <pthread.h>

# include "../libft/includes/libft.h"
# include "printf.h"
# include "debug.h"

typedef struct			s_chunk
{
	size_t				statut;
	size_t				size;
	size_t				align;
	struct s_chunk		*next;
}						t_chunk;

typedef struct			s_area
{
	size_t				size_used;
	size_t				size_max;
	t_chunk				*chunk;
	struct s_area		*next;
}						t_area;

typedef	struct			s_pages
{
	t_area				*small;
	t_area				*medium;
	t_area				*large;
	unsigned long long	checksum;
}						t_pages;

/*
**	Check if x64 or x86 for memory alignement
*/
# define MEM_ALIGN 16

# define SUCCESS	1
# define NOPE		0
# define ERROR		-1

# define FREE		1
# define USED		0
# define PERCENT_ALLOWED 80

# define TINY_SIZE		512
# define MEDIUM_SIZE	1024

# define AREA_SIZE		sizeof(t_area)
# define HEADER_SIZE	sizeof(t_chunk)

# define HEX "0123456789abcdef"

t_pages					g_page;
extern pthread_mutex_t	g_thread;

/*
**	malloc func
*/
void					*malloc(size_t size);
void					*malloc_protected(size_t size);
void					*manage_small_or_medium(size_t size);
void					*manage_large(size_t size, t_area **area);
t_area					*create_new_area(size_t size, t_area *prev);
t_area					*create_large_area(size_t size);
void					*search_free_chunk(size_t size, t_area *area);
t_area					*search_small_area(size_t size);
t_area					*search_medium_area(size_t size);

/*
**	free func
*/
void					free(void *ptr);
void					free_protected(void *ptr);
void					merge_previous_chunk(t_chunk *prev, t_chunk *current);
int						area_ready_to_free(t_area *area);

/*
**	realloc func
*/
void					*realloc(void *ptr, size_t size);
void					*realloc_protected(void *ptr, size_t size);
t_chunk					*larger_chunk_found(t_chunk *save, size_t aligned);
void					*realloc_new_chunk(t_chunk *save, void *ptr, size_t s);
/*
** calloc func
*/
void					*calloc_protected(size_t count, size_t size);
void					*calloc(size_t count, size_t size);

/*
**  utils
*/
size_t					align_size(size_t size, size_t align);
void					show_alloc_mem(void);
void					ft_puthex(unsigned long l);
void					ft_puthex_fd(unsigned long l, int fd);
void					ft_putaddr(void *ptr);

/*
** checksum generator
** thread protector
*/
unsigned long long		generate_checksum(void);
int						generate_new_checksum(void);
int						compare_checksum(void);
void					thread_protection_lock(void);
void					thread_protection_unlock(void);

#endif

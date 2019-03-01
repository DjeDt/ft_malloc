/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:56:42 by ddinaut           #+#    #+#             */
/*   Updated: 2019/02/28 23:09:02 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*search_in_this_one(t_chunk *chunk, void *ptr, \
									size_t size, size_t aligned)
{
	void	*ret;
	t_chunk	*save;

	ret = NULL;
	save = chunk;
	while (save != NULL)
	{
		if ((void*)save + HEADER_SIZE == ptr)
		{
			if (aligned <= save->size)
			{
				save = larger_chunk_found(save, aligned);
				return ((void*)save + HEADER_SIZE);
			}
			else
			{
				ret = realloc_new_chunk(save, ptr, size);
				return (ret);
			}
		}
		save = save->next;
	}
	return (NULL);
}

static void		*search_for_chunk(t_area *area, void *ptr, \
									size_t size, size_t aligned)
{
	void	*ret;
	t_area	*save;

	save = area;
	while (save != NULL)
	{
		ret = search_in_this_one(save->chunk, ptr, size, aligned);
		if (ret != NULL)
			return (ret);
		save = save->next;
	}
	return (NULL);
}

static void		*search_for_large_chunk(t_area *area, void *ptr, size_t size)
{
	void	*ret;
	t_area	*save;

	save = area;
	while (save != NULL)
	{
		if ((void*)save + AREA_SIZE == ptr)
		{
			ret = malloc_protected(size);
			ft_memcpy(ret, ptr, save->size_used);
			free_protected((void*)ptr - AREA_SIZE);
			return (ret);
		}
		save = save->next;
	}
	return (NULL);
}

static void		*check_area(void *ptr, size_t size)
{
	size_t	align;
	void	*ret;

	ret = NULL;
	compare_checksum();
	align = align_size(size, MEM_ALIGN);
	if ((ret = search_for_chunk(g_page.small, ptr, size, align)) != NULL)
		return (ret);
	else if ((ret = search_for_chunk(g_page.medium, ptr, size, align)) != NULL)
		return (ret);
	else if ((ret = search_for_large_chunk(g_page.large, ptr, size)) != NULL)
			return (ret);
	return (NULL);
}

void			*realloc_protected(void *ptr, size_t size)
{
	if (ptr == NULL)
		return (malloc_protected(size));
	return (check_area(ptr, size));
}

void			*realloc(void *ptr, size_t size)
{
	void *ret;

	thread_protection_lock();
	ret = realloc_protected(ptr, size);
	thread_protection_unlock();
	return (ret);
}

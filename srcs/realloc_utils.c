/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:39:46 by ddinaut           #+#    #+#             */
/*   Updated: 2019/03/01 13:11:33 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void     *search_in_this_one(t_chunk *chunk, void *ptr, \
                                    size_t size, size_t aligned)
{
	void    *ret;
	t_chunk *save;

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

void		*search_tiny_chunk(void *ptr, size_t size, size_t align)
{
	void	*ret;
	t_area	*save;

	save = g_page.small;
	while (save != NULL)
	{
		ret = search_in_this_one(save->chunk, ptr, size, align);
		if (ret != NULL)
			return (ret);
		save = save->next;
	}
	return (NULL);
}

void		*search_medium_chunk(void *ptr, size_t size, size_t align)
{
	void	*ret;
	t_area	*save;

	save = g_page.medium;
	while (save != NULL)
	{
		ret = search_in_this_one(save->chunk, ptr, size, align);
		if (ret != NULL)
			return (ret);
		save = save->next;
	}
	return (NULL);
}

void		*search_large_chunk(void *ptr, size_t size)
{
	void	*ret;
	t_area	*save;

	save = g_page.large;
	size = align_size(size, getpagesize());
	while (save != NULL)
	{
		if ((void*)save + AREA_SIZE == ptr)
		{
			ret = malloc_protected(size);
			if (size <= save->size_used)
				ft_memcpy(ret, ptr, size);
			else
				ft_memcpy(ret, ptr, save->size_used);
			free_protected(ptr);
			return (ret);
		}
		save = save->next;
	}
	return (NULL);
}

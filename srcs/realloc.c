/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:56:42 by ddinaut           #+#    #+#             */
/*   Updated: 2018/09/25 15:29:30 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*search_in_this_one(t_chunk *chunk, void *ptr, size_t size, size_t aligned)
{
	void	*ret;
	t_chunk	*save;

	ret = NULL;
	save = chunk;
	while (save != NULL)
	{
		if (save + HEADER_SIZE == ptr)
		{
			if (aligned < save->size)
			{
				save->size = aligned;
				return (ptr);
			}
			else
			{
				pthread_mutex_lock(&g_thread);
				ret = malloc(size);
				ft_memcpy(ret, ptr, save->size);
				free(ptr);
				pthread_mutex_unlock(&g_thread);
				return (ret);
			}
		}
		save = save->next;
	}
	return (NULL);
}

static void		*search_for_chunk(t_area *area, void *ptr, size_t size, size_t aligned)
{
	void	*ret;
	t_area	*save;

	save = area;
	while (save != NULL)
	{
		if ((ret = search_in_this_one(save->chunk, ptr, size, aligned)) != NULL)
			return (ret);
		save = save->next;
	}
	return (NULL);
}

static void		*check_area(void *ptr, size_t size)
{
	size_t	aligned;
	void	*ret;

	ret = NULL;
	aligned = ALIGN(size);
	if ((ret = search_for_chunk(g_page.small, ptr, size, aligned)) != NULL)
		return (ret);
	else if ((ret = search_for_chunk(g_page.medium, ptr, size, aligned)) != NULL)
		return (ret);
	else
	{
		/*
		** if can't realloc in smaller area or ptr can't be found, then have to malloc()
		** large chunk can't be reallocated since they have to be munmap() */
//		pthread_mutex_lock(&g_thread);
		ret = malloc(size);
		ft_memcpy(ret, ptr, size);
		free(ptr);
//		pthread_mutex_unlock(&g_thread);
		return (ret);
	}
}

void	*realloc(void *ptr, size_t size)
{
	if (ptr == NULL)
		return (malloc(size));
	return (check_area(ptr, size));
}

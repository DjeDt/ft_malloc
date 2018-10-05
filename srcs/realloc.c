/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:56:42 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/05 13:29:10 by ddinaut          ###   ########.fr       */
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
		if ((char*)save + HEADER_SIZE == ptr)
		{
			if (aligned < save->size)
			{
				save->size = aligned;
				return (ptr);
			}
			else
			{
				ret = malloc(size);
				ft_memcpy(ret, ptr, save->size);
				free(ptr);
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
		if ((ret = search_in_this_one(save->chunk, ptr, size, aligned)) != NULL)
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
		if ((char*)save + AREA_SIZE == ptr)
		{
			ret = malloc(size);
			ft_memcpy(ret, ptr, save->size_used);
			free(ptr);
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
	align = align_size(size);
	if ((ret = search_for_chunk(g_page.small, ptr, size, align)) != NULL)
		return (ret);
	else if ((ret = search_for_chunk(g_page.medium, ptr, size, align)) != NULL)
		return (ret);
	else if ((ret = search_for_large_chunk(g_page.large, ptr, size)) != NULL)
		return (ret);
	else
		return (NULL);
}

void			*realloc(void *ptr, size_t size)
{
	if (ptr == NULL)
		return (malloc(size));
	return (check_area(ptr, size));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:56:42 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/21 19:29:35 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
**	check if chunk can extend to size
**	if not, free() and malloc()
*/

static int		enough_space(t_chunk *chunk, size_t size)
{
	if (chunk->next != NULL)
	{
		if ((chunk->data + size) < chunk->next->data)
			return (SUCCESS);
	}
	return (NOPE);
}

static void		*search_in_this_one(t_chunk *chunk, void *ptr, size_t size)
{
	void	*ret;
	t_chunk	*save;

	save = chunk;
	while (save != NULL)
	{
		if (save->data == ptr)
		{
			if (enough_space(save, size) == SUCCESS)
			{
				save->size = size;
				return (save->data);
			}
			else
			{
				ret = malloc(size);
				ret = ft_memcpy(ret, ptr, save->size);
				free(ptr);
				return (ret);
			}
		}
		save = save->next;
	}
	return (NULL);
}

static void		*search_for_chunk(t_area *area, void *ptr, size_t size)
{
	void	*ret;
	t_area	*save;

	save = area;
	while (save != NULL)
	{
		if ((ret = search_in_this_one(save->chunk, ptr, size)) != NULL)
			return (ret);
		save = save->next;
	}
	return (NULL);
}

static void		*check_area(void *ptr, size_t size)
{
	void	*ret;

	if ((ret = search_for_chunk(g_page.small, ptr, size)) != NULL)
		return (ret);
	else if ((ret = search_for_chunk(g_page.medium, ptr, size)) != NULL)
		return (ret);
	else
	{
		/* large chunk can't be reallocated since they have to be munmap() */
		ret = malloc(size);
		ret = ft_memcpy(ret, ptr, size);
		free(ptr);
	}
	return (ret);
}

void	*realloc(void *ptr, size_t size)
{
	ft_putstr("[realloc] : ");
	ft_putnbr(size);
	ft_putchar('\n');

	if (size == 0)
		return (realloc(ptr, 16));
	if (ptr == NULL)
		ptr = malloc(size);
	else if (ptr != NULL && size == 0)
	{
		free(ptr);
		ptr = malloc(16);
	}
	else
		ptr = check_area(ptr, size);
	return (ptr);
}

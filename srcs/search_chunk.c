/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_chunk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:24:48 by ddinaut           #+#    #+#             */
/*   Updated: 2018/04/09 18:34:24 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*search_free_chunk(t_area *area, size_t size)
{
	t_area	*save;
	t_chunk	*tmp;

	save = area;

	if (DEBUG == 1)
		ft_putendl("[malloc] search_free chunk");
	while (save != NULL)
	{
		tmp = save->chunk;
		while (tmp != NULL)
		{
			if ((tmp->size >= size) && (tmp->statut == FREE))
			{
				tmp->statut = USED;
				return (tmp + HEADER_SIZE);
			}
			tmp = tmp->next;
		}
		save = save->next;
	}
	return (NULL);
}

t_area	*search_small_area(size_t size)
{
	t_area	*save;
	t_area	*prev;

	save = g_page.small;
	if (save == NULL)
	{
		save = create_new_area(TINY_SIZE, NULL);
		return (save);
	}
	while (save != NULL)
	{
		if ((save->size_used + size) < save->size_max)
			return (save);
		prev = save;
		save = save->next;
	}
	if (save == NULL)
	{
		prev = create_new_area(TINY_SIZE, prev);
		return (prev->next);
	}
	return (NULL);
}

t_area	*search_medium_area(size_t size)
{
	t_area	*save;
	t_area	*prev;

	save = g_page.medium;
	if (save == NULL)
	{
		save = create_new_area(MEDIUM_SIZE, NULL);
		return (save);
	}
	while (save != NULL)
	{
		if ((save->size_used + size) < save->size_max)
			return (save);
		prev = save;
		save = save->next;
	}
	if (save == NULL)
	{
		prev = create_new_area(MEDIUM_SIZE, prev);
		return (prev->next);
	}
	return (NULL);
}

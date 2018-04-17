/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_chunk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:24:48 by ddinaut           #+#    #+#             */
/*   Updated: 2018/04/16 18:16:26 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*search_free_chunk(t_area *area, size_t size)
{
	t_area	*save;
	t_chunk	*tmp;

	save = area;
	while (save != NULL)
	{
		tmp = save->chunk;
		while (tmp != NULL)
		{
			if ((tmp->size >= size) && (tmp->statut == FREE))
			{
				tmp->statut = USED;
				return ((unsigned char*)tmp + HEADER_SIZE);
			}
			tmp = tmp->next;
		}
		save = save->next;
	}
	return (NULL);
}

t_area	*search_small_area(size_t size, t_area **area)
{
	t_area *tmp;
	t_area *prev;

	tmp = (*area);
	if (tmp == NULL)
	{
		(*area) = create_new_area(TINY_SIZE, NULL);
		return (*area);
	}
	else
	{
		while (tmp != NULL)
		{
			if ((tmp->size_used + size) < tmp->size_max)
				return (tmp);
			prev = tmp;
			tmp = tmp->next;
		}
		if (tmp == NULL)
		{
			tmp = create_new_area(TINY_SIZE, prev);
			prev->next = tmp;
		}
		return (tmp);
	}
	return (NULL);
}

t_area	*search_medium_area(size_t size, t_area **area)
{
	t_area *tmp;
	t_area *prev;

	tmp = (*area);
	if (tmp == NULL)
	{
		(*area) = create_new_area(MEDIUM_SIZE, NULL);
		return (*area);
	}
	else
	{
		while (tmp != NULL)
		{
			if ((tmp->size_used + size) < tmp->size_max)
				return (tmp);
			prev = tmp;
			tmp = tmp->next;
		}
		if (tmp == NULL)
		{
			tmp = create_new_area(MEDIUM_SIZE, prev);
			prev->next = tmp;
		}
		return (tmp);
	}
	return (NULL);
}


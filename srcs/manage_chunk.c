/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_chunk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:42:26 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/18 11:57:32 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*push_chunk(size_t size, t_area *area)
{
	t_chunk	*tmp;
	t_chunk *new;

	new = (void*)area + area->size_used;
	new->size = size;
	new->statut = USED;
	new->align = 0;
	new->next = NULL;
	area->size_used += (size + HEADER_SIZE);
	if (area->chunk == NULL)
		area->chunk = new;
	else
	{
		tmp = area->chunk;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return ((void*)new + HEADER_SIZE);
}

void		*manage_large(size_t size, t_area **area)
{
	t_area	*new;
	t_area	*tmp;

	if ((*area) == NULL)
	{
		(*area) = create_large_area(size);
		return ((void*)area + AREA_SIZE);
	}
	else
	{
		new = create_large_area(size);
		tmp = (*area);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return ((void*)new + AREA_SIZE);
}

void		*manage_small_or_medium(size_t size)
{
	void	*ret;
	t_area	*area;

	ret = NULL;
	area = NULL;
	if (size <= TINY_SIZE)
	{
		if ((ret = search_free_chunk(size, g_page.small)) != NULL)
			return (ret);
		area = search_small_area(size);
	}
	else
	{
		if ((ret = search_free_chunk(size, g_page.medium)) != NULL)
			return (ret);
		area = search_medium_area(size);
	}
	if (!area)
		return (NULL);
	ret = push_chunk(size, area);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_chunk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:42:26 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/05 13:34:59 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*push_chunk(size_t size, t_area *area)
{
	t_chunk	*tmp;
	t_chunk *new;

	new = (t_chunk*)((char*)area + area->size_used);
	new->size = size;
	new->statut = USED;
	new->next = NULL;
	area->size_used += (size + HEADER_SIZE);
	tmp = area->chunk;
	if (tmp == NULL)
		area->chunk = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return ((char*)new + HEADER_SIZE);
}

void		*manage_large(size_t size, t_area **area)
{
	t_area	*tmp;

	if ((*area) == NULL)
	{
		(*area) = create_large_area(size);
		return ((char*)(*area) + AREA_SIZE);
	}
	else
	{
		tmp = (*area);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = create_large_area(size);
	}
	return ((char*)tmp->next + AREA_SIZE);
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
	if (area == NULL)
		return (NULL);
	ret = push_chunk(size, area);
	return (ret);
}

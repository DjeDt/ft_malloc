/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:42:26 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/21 19:11:15 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	init_chunk(t_chunk **chunk, size_t size)
{
	(*chunk)->size = size;
	(*chunk)->data = (*chunk) + HEADER_SIZE;
	(*chunk)->statut = USED;
	(*chunk)->next = NULL;
	(*chunk)->prev = NULL;
}

void	*push_chunk(t_area *area, size_t size)
{
	t_chunk	*tmp;
	t_chunk *new;

	new = area->map + area->size_used;
	init_chunk(&new, size);
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
	return (new->data);
}

void	*push_large(t_area *area, size_t size)
{
	t_area	*new;
	t_area	*tmp;

	new = create_large_area(size);
	if (area == NULL)
		area = new;
	else
	{
		tmp = area;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new->map);
}

void	*push_chunk_to_area(size_t size)
{
	void	*ret;
	t_area	*area;

	ret = NULL;
	area = NULL;
	if (size <= TINY_SIZE)
	{
		if ((ret = search_free_chunk(g_page.small, size)) != NULL)
			return (ret);
		area = search_small_area(size);
		ret = push_chunk(area, size);
	}
	else if (size <= MEDIUM_SIZE)
	{
		if ((ret = search_free_chunk(g_page.medium, size)) != NULL)
			return (ret);
		area = search_medium_area(size);
		ret = push_chunk(area, size);
	}
	else
		ret = push_large(g_page.large, size);
	return (ret);
}

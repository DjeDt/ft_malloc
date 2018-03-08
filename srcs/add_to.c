/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 15:27:29 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/08 21:16:20 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	init_chunk(t_chunk **chunk, size_t size)
{
	(*chunk)->size = size;
	(*chunk)->prev_size = 0;
	(*chunk)->statut = USED;
	(*chunk)->previous = NULL;
	(*chunk)->next = NULL;
}

void go_to_the_end(t_chunk **lst, t_chunk **new)
{
	t_chunk *tmp;

	if ((*lst) == NULL)
		(*lst) = (*new);
	else
	{
		tmp = (*lst);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = (*new);
		tmp->next->prev_size = tmp->size;
		tmp->next->previous = tmp;
	}
}

t_chunk	*push_to_smaller_area(t_area *area, size_t size)
{
	t_chunk	*new;
	size_t	total;

	total = size + HEADER_SIZE;
	new = area->map + area->size_used;
	init_chunk(&new, size);
	area->size_used += total;
	go_to_the_end(&area->chunk, &new);
	return (new);
}

t_chunk	*push_to_large_area(size_t size)
{
	t_chunk	*new;
	t_area	*save;

	save = g_page.large;
	while (g_page.large->next != NULL)
		g_page.large = g_page.large->next;
	new = g_page.large->map;
	init_chunk(&new, size);
	g_page.large->size_used += size;
	g_page.large = save;
	go_to_the_end(&g_page.large->chunk, &new);
	return (new);
}

t_chunk	*push_chunk_to_area(size_t size)
{
	void	*ret;

	ret = NULL;
	if (size <= TINY_SIZE)
		ret = push_to_smaller_area(g_page.small, size);
	else if (size <= MEDIUM_SIZE)
		ret = push_to_smaller_area(g_page.medium, size);
	else
		ret = push_to_large_area(size);
	return (ret + HEADER_SIZE);
}

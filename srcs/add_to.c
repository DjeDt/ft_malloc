/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 15:27:29 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/07 20:35:56 by ddinaut          ###   ########.fr       */
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

void	go_to_the_end(t_chunk **lst, t_chunk *new)
{
	t_chunk *tmp;

	if ((*lst) == NULL)
		(*lst) = new;
	else
	{
		tmp = (*lst);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		tmp->next->prev_size = tmp->size;
		tmp->next->previous = tmp;
	}
}

void	*push_to_small_area(size_t size)
{
	t_chunk	*new;
	size_t	total;

	total = size + HEADER_SIZE;
	new = g_page.small->map + g_page.small->size_used;
	init_chunk(&new, size);
	g_page.small->size_used += total;
	go_to_the_end(&g_page.small->chunk, new);
	return (new + HEADER_SIZE);
}

void	*push_to_medium_area(size_t size)
{
	t_chunk	*new;
	size_t	total;

	total = size + HEADER_SIZE;
	new = g_page.medium->map + g_page.medium->size_used;
	init_chunk(&new, size);
	g_page.medium->size_used += total;
	go_to_the_end(&g_page.medium->chunk, new);
	return (new + HEADER_SIZE);
}

void	*push_to_large_area(size_t size)
{
	t_chunk	*new;
	t_area	*save;

	save = g_page.large;
	while (g_page.large->next != NULL)
		g_page.large = g_page.large->next;
	new = g_page.large->map;
	init_chunk(&new, size);
	g_page.large->size_used += size;
	go_to_the_end(&g_page.large->chunk, new);
	g_page.large = save;
	return (new + HEADER_SIZE);
}

void	*push_chunk(size_t size)
{
	void	*ret;

	if (size <= TINY_SIZE)
		ret = push_to_small_area(size);
	else if (size <= MEDIUM_SIZE)
		ret = push_to_medium_area(size);
	else
		ret = push_to_large_area(size);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 15:27:29 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/09 18:46:52 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	init_chunk(t_chunk **chunk, size_t size)
{
	(*chunk)->size = size;
	(*chunk)->data = (*chunk) + sizeof(size_t);
	(*chunk)->statut = USED;
	(*chunk)->next = NULL;
	(*chunk)->prev = NULL;
}

void go_to_the_end(t_chunk **lst, t_chunk **new)
{
	t_chunk *tmp;

	if ((*lst) == NULL)
	{
		(*lst) = (*new);
//		printf("[add to 1] %p\n", (*lst)->data);
	}
	else
	{
		tmp = (*lst);
		while (tmp->next != NULL)
			tmp = tmp->next;
		(*new)->prev = tmp;
		(*new)->next = NULL;
		tmp->next = (*new);
//		printf("[add to 1] %p\n", tmp->next->data);
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

	printf("[add to 2] %p\n", new->data);
	return (new->data);
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

	printf("[add to 2] %p\n", new->data);
	return (new->data);
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
	printf("[add to 3] %p\n", ret);
	return (ret);
}

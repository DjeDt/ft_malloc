/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 15:27:29 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/14 19:31:35 by ddinaut          ###   ########.fr       */
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
		(*lst) = (*new);
	else
	{
		tmp = (*lst);
		while (tmp->next != NULL)
			tmp = tmp->next;
		(*new)->prev = tmp;
		if (tmp->next != NULL)
			(*new)->next = tmp->next->next;
		tmp->next = (*new);
	}
}

t_chunk	*extract_chunk_from_bin(t_chunk **lst, size_t size)
{
	t_chunk *tmp;

	if ((*lst) == NULL)
		return (NULL);
	tmp = (*lst);
	while (tmp != NULL)
	{
		if (tmp->size >= size)
		{
			rebuilt_area_chunk(&tmp);
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

t_chunk	*push_to_smaller_area(t_area *area, size_t size)
{
	t_chunk	*new;
	size_t	total;

	(void)area;
	/*
	while ((area != NULL) && (area->size_max - area->size_used >= size))
		area = area->next;
	if (area == NULL)
		[...]
	*/
	total = size + HEADER_SIZE;
	
	if ((new = extract_chunk_from_bin(&g_page.bin, size)) == NULL)
	{
		printf("[push chunk not found]\n");
		new = area->map + area->size_used;
	}
	init_chunk(&new, size);
	area->size_used += total;
	go_to_the_end(&area->chunk, &new);
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
	return (new->data);
}

/*
t_chunk	*search_free_chunk(t_chunk **bin, size_t size)
{
	t_chunk *tmp;

	if ((*bin) == NULL)
		return (NULL);
	tmp = extract_chunk_from_bin(bin, size);
	if (tmp == NULL)
		return (NULL);
	rebuilt_area_chunk(&tmp);
	tmp->statut = USED;
	tmp->size = size;
	if (size <= TINY_SIZE)
		go_to_the_end(&g_page.small->chunk, &tmp);
	else if (size <= MEDIUM_SIZE)
		go_to_the_end(&g_page.medium->chunk, &tmp);
	return (tmp->data);
}
*/
t_chunk	*push_chunk_to_area(size_t size)
{
	void	*ret;

	ret = NULL;
	if (size <= TINY_SIZE)
	{
//		if ((ret = search_free_chunk(&g_page.bin, size)) == NULL)
			ret = push_to_smaller_area(g_page.small, size);
	}
	else if (size <= MEDIUM_SIZE)
	{
//		if ((ret = search_free_chunk(&g_page.bin, size)) == NULL)
			ret = push_to_smaller_area(g_page.medium, size);
	}
	else
	{
		ret = push_to_large_area(size);
	}
	return (ret);
}

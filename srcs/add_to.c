/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 15:27:29 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/15 17:26:16 by ddinaut          ###   ########.fr       */
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

void	go_to_the_end(t_chunk **lst, t_chunk **new)
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

t_chunk		*extract_chunk_from_bin(t_chunk **lst, size_t size)
{
	t_chunk *tmp;

	if ((*lst) == NULL)
		return (NULL);
	tmp = (*lst);
	while (tmp != NULL)
	{
		if (tmp->size >= size)
		{
			rebuilt_area_chunk(&tmp, lst);
			tmp->statut = USED;
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

t_area		*search_area(t_area **area, size_t size, size_t type)
{
	t_area	*tmp;
	t_area	*prev;

	tmp = (*area);
	prev =  NULL;
	while (tmp != NULL)
	{
		if ((tmp->size_max - tmp->size_used) >= size)
			return (tmp);
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		if (check_small_area2(&tmp, type) != SUCCESS)
			return (NULL);
		prev->next = tmp;
	}
	return (prev->next);
}

t_chunk		*push_to_smaller_area(t_area *area, size_t size)
{
	t_chunk	*new;
	size_t	total;

	total = size + HEADER_SIZE;
	if ((new = extract_chunk_from_bin(&g_page.bin, size)) == NULL)
	{
		new = area->map + area->size_used;
		init_chunk(&new, size);
		area->size_used += total;
	}
	go_to_the_end(&area->chunk, &new);
	return (new->data);
}

t_chunk	*push_to_large_area(t_area **area, size_t size)
{
	size_t	total;
	t_chunk	*new;
	t_area	*tmp;

	tmp = (*area);
	while (tmp != NULL)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	
	/*
	total = size + HEADER_SIZE;
	save = g_page.large;
	while (g_page.large->next != NULL)
		g_page.large = g_page.large->next;

	new = g_page.large->map + HEADER_SIZE;
	init_chunk(&new, size);
	g_page.large->size_used += total;
	g_page.large = save;
//	go_to_the_end(&g_page.large->chunk, &new);
*/
	return (new->data);
}

t_chunk	*push_chunk_to_area(size_t size)
{
	void	*ret;
	t_area	*area;

	ret = NULL;
	if (size <= TINY_SIZE)
	{
		if ((area = search_area(&g_page.small, size, TINY_SIZE)) == NULL)
			return (NULL);
		ret = push_to_smaller_area(area, size);
	}
	else if (size <= MEDIUM_SIZE)
	{
		if ((area = search_area(&g_page.medium, size, MEDIUM_SIZE)) == NULL)
			return (NULL);
		ret = push_to_smaller_area(area, size);
	}
	else
		ret = push_to_large_area(&g_page.large ,size);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 15:27:29 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/19 19:24:25 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_area	*create_large_arena(size_t size)
{
	size_t	total;
	t_area	*new;

	(void)total;
	new = mmap(NULL, size + AREA_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (new == MAP_FAILED)
	{
		ft_putendl_fd("allocation error. not enought space left.", 2);
		return (NULL);
	}
	new->size_used = size;
	new->size_max = size;
	new->map = new + AREA_SIZE;
	new->chunk = NULL;
	new->next = NULL;
	return (new);
}

void	*push_to_large_area(t_area **area, size_t size)
{
	t_area	*tmp;

	if ((*area) == NULL)
	{
		(*area) = create_large_arena(size);
		return ((*area)->map);
	}
	else
	{
		tmp = (*area);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = create_large_arena(size);
		return (tmp->next->map);
	}
}

/*
**	Unused since i removed bin linked list
**	Use search_free_chunk() instead
*/
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
			rebuilt_area_chunk(&tmp);
			tmp->statut = USED;
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

t_chunk	*search_free_chunk(t_chunk **lst, size_t size)
{
	t_chunk *tmp;

	if ((*lst) == NULL)
		return (NULL);
	tmp = (*lst);
	while (tmp != NULL)
	{
		if (tmp->size >= size)
		{
			tmp->statut = USED;
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	init_chunk(t_chunk **chunk, size_t size)
{
	(*chunk)->size = size;
	(*chunk)->data = (*chunk) + HEADER_SIZE;
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

t_area		*search_area(t_area **area, size_t size, size_t type)
{
	t_area	*tmp;
	t_area	*prev;

	tmp = (*area);
	prev = NULL;
	while (tmp != NULL)
	{
		if ((tmp->size_used + size) < tmp->size_max)
			return (tmp);
		prev = tmp;
		tmp = tmp->next;
	}
	if (check_another_area(&prev->next, prev, type) != SUCCESS)
		return (NULL);
	return (prev->next);
}

void	*push_to_smaller_area(t_area *area, size_t size)
{
	t_chunk	*new;
	size_t	total;

	new = NULL;
	total = size + HEADER_SIZE;
	if ((new = search_free_chunk(&area->chunk, size)) == NULL)
	{
		new = area->map + area->size_used;
		init_chunk(&new, size);
		area->size_used += total;
		go_to_the_end(&area->chunk, &new);
	}
	return (new->data);
}

void	*push_chunk_to_area(size_t size)
{
	void	*ret;
	t_area	*area;

	ret = NULL;
	area = NULL;
	if (size <= TINY_SIZE)
	{
		if ((area = search_area(&g_page.small, size, TINY_SIZE)) != NULL)
			ret = push_to_smaller_area(area, size);
	}
	else if (size <= MEDIUM_SIZE)
	{
		if ((area = search_area(&g_page.medium, size, MEDIUM_SIZE)) != NULL)
			ret = push_to_smaller_area(area, size);
	}
	else
		ret = push_to_large_area(&g_page.large ,size);
	return (ret);
}

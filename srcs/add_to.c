/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 15:27:29 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/16 20:29:06 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_area	*create_large_arena(size_t size)
{
	t_area *new;

	new = mmap(NULL, size + AREA_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (new == MAP_FAILED)
	{
		ft_putendl_fd("allocation error. not enought space left.", 2);
		return (NULL);
	}
	new->size_used = size;
	new->size_max = size;
	new->map = new + (sizeof(size_t) * 2);
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
	tmp = (*area);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = create_large_arena(size);
	return (tmp->next->map);
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
		ft_putendl("create area");
		if (check_another_area(&tmp, type) != SUCCESS)
			return (NULL);
		ft_putendl("create 1");
		prev->next = tmp;
		ft_putendl("create 2");
	}
	return (prev->next);
}

void	*push_to_smaller_area(t_area *area, size_t size)
{
	t_chunk	*new;
	size_t	total;

	total = size + HEADER_SIZE;
	if ((new = extract_chunk_from_bin(&g_page.bin, size)) == NULL)
	{
		printf("[SIZE SIZE]%zu\n", area->size_used);
		new = area->map + area->size_used;
		ft_putendl("push 1");
		init_chunk(&new, size);
		ft_putendl("push 2");
		area->size_used += total;
	}
	go_to_the_end(&area->chunk, &new);
	return (new->data);
}

void	*push_chunk_to_area(size_t size)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:42:26 by ddinaut           #+#    #+#             */
/*   Updated: 2018/04/20 11:56:32 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	init_chunk(t_chunk **chunk, size_t size)
{
	(*chunk)->size = size;
	(*chunk)->statut = USED;
	(*chunk)->next = NULL;
}

static void	*push_chunk(t_area *area, size_t size)
{
	t_chunk	*tmp;
	t_chunk *new;

	if (area == NULL)
		return (NULL);
	new = (void*)area + area->size_used;
	init_chunk(&new, size);
	area->size_used += size;
	tmp = area->chunk;
	if (tmp == NULL)
		area->chunk = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return ((unsigned char*)new + HEADER_SIZE);
}

static void	*push_large(t_area **area, size_t size)
{
	t_area	*tmp;

//	pthread_mutex_lock(&g_thread);
	if ((*area) == NULL)
	{
		(*area) = create_large_area(size);
//		pthread_mutex_unlock(&g_thread);
		return ((unsigned char*)*area + AREA_SIZE);
	}
	else
	{
		tmp = (*area);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = create_large_area(size);
	}
//	pthread_mutex_unlock(&g_thread);
	return ((unsigned char*)tmp->next + AREA_SIZE);
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
//		pthread_mutex_lock(&g_thread);
		if ((area = search_small_area(size, &g_page.small)) == NULL)
			return (NULL);
		ret = push_chunk(area, size);
//		pthread_mutex_unlock(&g_thread);
	}
	else if (size <= MEDIUM_SIZE)
	{
		if ((ret = search_free_chunk(g_page.medium, size)) != NULL)
			return (ret);
//		pthread_mutex_lock(&g_thread);
		if ((area = search_medium_area(size, &g_page.medium)) == NULL)
			return (NULL);
		ret = push_chunk(area, size);
//		pthread_mutex_unlock(&g_thread);
	}
	else
		ret = push_large(&g_page.large, size);
	return (ret);
}

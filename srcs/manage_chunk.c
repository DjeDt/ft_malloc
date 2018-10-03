/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_chunk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:42:26 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/03 10:39:01 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*push_chunk(size_t size, t_area *area)
{
	t_chunk	*tmp;
	t_chunk *new;

	new = (t_chunk*)area + area->size_used;
	new->size = size;
	new->statut = USED;
	new->next = NULL;
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
	return (new + HEADER_SIZE);
}

void	*manage_large(size_t size, t_area **area)
{
	t_area	*tmp;

	if ((*area) == NULL)
	{

//		pthread_mutex_lock(&g_thread);
		(*area) = create_large_area(size);
//		pthread_mutex_unlock(&g_thread);
		return ((*area)->chunk);
	}
	else
	{
		tmp = (*area);
		while (tmp->next != NULL)
			tmp = tmp->next;
//	pthread_mutex_lock(&g_thread);
		tmp->next = create_large_area(size);
//	pthread_mutex_unlock(&g_thread);
	}
	return (tmp->next->chunk + AREA_SIZE);
}

void	*manage_small_or_medium(size_t size)
{
	void	*ret;
	t_area	*area;

	ret = NULL;
	area = NULL;
//		pthread_mutex_lock(&g_thread);
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
//		pthread_mutex_unlock(&g_thread);
}

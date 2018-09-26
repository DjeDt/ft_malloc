/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_chunk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:42:26 by ddinaut           #+#    #+#             */
/*   Updated: 2018/09/26 17:34:03 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	init_chunk(t_chunk **chunk, size_t size)
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

	if (ENABLE_DEBUG == ENABLE)
	{
		ft_putstr("param size: ");
		ft_putnbr(size);
		ft_putstr("  size_used = ");
		ft_putnbr(area->size_used);
		ft_putchar('\n');
	}
	new = (void*)area + area->size_used;

//	init_chunk(&new, size);
	new->size = size;
	new->statut = USED;
	new->next = NULL;

	if (ENABLE_DEBUG == ENABLE)
	{
		ft_putstr("area->size_used = ");
		ft_putnbr(area->size_used);
		ft_putstr(" [-> is now -> ] ");
		ft_putnbr(area->size_used + size);
		ft_putchar('\n');
	}

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

void	*manage_large(t_area **area, size_t size)
{
	t_area	*tmp;

	pthread_mutex_lock(&g_thread);
	if ((*area) == NULL)
	{
		(*area) = create_large_area(size);
		pthread_mutex_unlock(&g_thread);
		return ((unsigned char*)*area + AREA_SIZE);
	}
	else
	{
		tmp = (*area);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = create_large_area(size);
	}
	pthread_mutex_unlock(&g_thread);
	return ((unsigned char*)tmp->next + AREA_SIZE);
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
		if ((ret = search_free_chunk(g_page.small, size)) != NULL)
			return (ret);
		area = search_small_area(size, &g_page.small);
	}
	else
	{
		if ((ret = search_free_chunk(g_page.medium, size)) != NULL)
			return (ret);
		area = search_medium_area(size, &g_page.medium);
	}
	if (area == NULL)
		return (NULL);
	ret = push_chunk(area, size);
	return (ret);
//		pthread_mutex_unlock(&g_thread);
}

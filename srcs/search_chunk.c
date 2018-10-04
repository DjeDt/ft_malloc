/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_chunk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:24:48 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/04 19:59:25 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*search_free_chunk(size_t size, t_area *area)
{
	t_area	*save;
	t_chunk	*tmp;

	save = area;
	while (save != NULL)
	{
		tmp = save->chunk;
		while (tmp != NULL)
		{
			if (tmp->size >= size && tmp->statut == FREE)
			{
				tmp->statut = USED;
				return ((char*)tmp + HEADER_SIZE);
			}
			tmp = tmp->next;
		}
		save = save->next;
	}
	return (NULL);
}

t_area	*search_small_area(size_t size)
{
	t_area *tmp;
	t_area *prev;

	if (g_page.small == NULL)
	{
	    g_page.small = create_new_area(TINY_SIZE, NULL);
		return (g_page.small);
	}
	else
	{
		tmp = g_page.small;
		while (tmp != NULL)
		{
			if ((tmp->size_used + size) < tmp->size_max)
				break ;
			prev = tmp;
			tmp = tmp->next;
		}
		if (tmp == NULL)
			tmp = create_new_area(TINY_SIZE, prev);
		return (tmp);
	}
	return (NULL);
}

t_area	*search_medium_area(size_t size)
{
	t_area *tmp;
	t_area *prev;

	if (g_page.medium == NULL)
	{
		g_page.medium = create_new_area(MEDIUM_SIZE, NULL);
		return (g_page.medium);
	}
	else
	{
		tmp = g_page.medium;
		while (tmp != NULL)
		{
			if ((tmp->size_used + size) < tmp->size_max)
				break ;
			prev = tmp;
			tmp = tmp->next;
		}
		if (tmp == NULL)
			tmp = create_new_area(MEDIUM_SIZE, prev);
		return (tmp);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 20:30:59 by ddinaut           #+#    #+#             */
/*   Updated: 2019/02/28 18:57:05 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <errno.h>
#include <stdio.h>

static int	search_large(t_area **area, void *ptr)
{
	t_area	*save;
	t_area	*prev;

	prev = NULL;
	save = (*area);
	while (save != NULL)
	{
		if ((void*)save + AREA_SIZE == ptr)
		{
			if (prev != NULL)
				prev->next = save->next;
			else
				(*area) = save->next;
			munmap(save, save->size_max);
			return (SUCCESS);
		}
		prev = save;
		save = save->next;
	}
	return (NOPE);
}

static int	search_for_chunk(t_chunk *list, void *ptr)
{
	t_chunk *save;
	t_chunk	*prev;

	save = list;
	prev = NULL;
	while (save != NULL)
	{
		if ((void*)save + HEADER_SIZE == ptr)
		{
			save->statut = FREE;
			if (prev != NULL)
				merge_previous_chunk(prev, save);
			else if (save->next != NULL && save->next->statut == FREE)
			{
				save->size += (save->next->size + HEADER_SIZE);
				save->next = save->next->next;
			}
			return (SUCCESS);
		}
		prev = save;
		save = save->next;
	}
	return (NOPE);
}

static int	search_smaller(t_area *area, void *ptr)
{
	t_area	*prev;
	t_area	*save;

	prev = NULL;
	save = area;
	while (save != NULL)
	{
		if (search_for_chunk(save->chunk, ptr) == SUCCESS)
		{
			if (area_ready_to_free(save) == SUCCESS)
			{
				if (prev != NULL)
					prev->next = save->next;
				else
					area = save->next;
				munmap(save, save->size_max);
			}
			return (SUCCESS);
		}
		prev = save;
		save = save->next;
	}
	return (NOPE);
}

void		free_protected(void *ptr)
{
	if (ptr == NULL)
		return ;
	compare_checksum();
	if (search_smaller(g_page.small, ptr) != SUCCESS)
	{
		if (search_smaller(g_page.medium, ptr) != SUCCESS)
			search_large(&g_page.large, ptr);
	}
	generate_new_checksum();
}

void		free(void *ptr)
{
	thread_protection_lock();
	free_protected(ptr);
	thread_protection_unlock();
}

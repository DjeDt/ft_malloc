/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 20:30:59 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/17 15:18:01 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	search_large(t_area **area, void *ptr)
{
	t_area	*save;
	t_area	*prev;
	int		ret;

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
			ret = munmap(save, save->size_max);
			return (ret == 0 ? SUCCESS : ERROR);
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
				if (munmap(save, save->size_max) != 0)
					ft_putendl_fd("error when unmap memory", STDERR_FILENO);
			}
			return (SUCCESS);
		}
		prev = save;
		save = save->next;
	}
	return (NOPE);
}

void		free(void *ptr)
{
	if (ptr == NULL)
		return ;
	thread_protection_lock();
	compare_checksum();
	if (search_smaller(g_page.small, ptr) != SUCCESS)
	{
		if (search_smaller(g_page.medium, ptr) != SUCCESS)
		{
			if (search_large(&g_page.large, ptr) == ERROR)
				ft_putendl_fd("error when unmap memory", STDERR_FILENO);
		}
	}
	generate_new_checksum();
	thread_protection_unlock();
}

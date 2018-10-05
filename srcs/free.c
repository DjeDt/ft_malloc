/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 20:30:59 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/05 15:03:56 by ddinaut          ###   ########.fr       */
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
		if ((char*)save + AREA_SIZE == ptr)
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

	save = list;
	while (save != NULL)
	{
		if ((char*)save + HEADER_SIZE == ptr)
		{
			save->statut = FREE;
			return (SUCCESS);
		}
		save = save->next;
	}
	return (NOPE);
}

static int	search_smaller(t_area *area, void *ptr)
{
	t_area *save;

	save = area;
	while (save != NULL)
	{
		if (search_for_chunk(save->chunk, ptr) == SUCCESS)
			return (SUCCESS);
		save = save->next;
	}
	return (NOPE);
}

void		free(void *ptr)
{
	if (ptr == NULL)
		return ;
	thread_protection_lock();
	if (ENABLE_CHECKSUM == ENABLE && generate_checksum() != g_page.cheksum)
		ft_putendl_fd("error, hash differs, corrupt data", STDERR_FILENO);
	if (search_smaller(g_page.small, ptr) != SUCCESS)
	{
		if (search_smaller(g_page.medium, ptr) != SUCCESS)
		{
			if (search_large(&g_page.large, ptr) == ERROR)
				ft_putendl_fd("error when unmap memory", STDERR_FILENO);
		}
	}
	if (ENABLE_CHECKSUM == ENABLE)
		g_page.cheksum = generate_checksum();
	thread_protection_unlock();
}

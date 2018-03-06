/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 20:30:59 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/06 18:35:06 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		search_chunk(t_chunk **zone, void *ptr)
{
	t_chunk	*tmp;

	tmp = (*zone);
	while (tmp != NULL)
	{
		if (tmp == (ptr - HEADER_SIZE))
		{
			if (munmap(tmp, tmp->size) == -1) /* have to find out how to keep the header */
				perror("munmap : "); /* just for debug */
			tmp->statut = FREE;  /* segfault */
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	search_zone(t_pages *page, void *ptr)
{
	int		ret;

	ret = 0;
	if (page->tiny != NULL)
	{
		ret = search_chunk(&page->tiny, ptr);
	}
	if (ret == 0 && page->medium != NULL)
	{
		ret = search_chunk(&page->medium, ptr);
	}
	if (ret == 0 && page->large != NULL)
	{
		ret = search_chunk(&page->large, ptr);
	}
	/*
	if (page->tiny != NULL)
		ret = search_chunk(&page->tiny, ptr);
	if (ret == 0 && page->medium != NULL)
		ret = search_chunk(&page->medium, ptr);
	if (ret == 0 && page->large != NULL)
		ret = search_chunk(&page->large, ptr);
	if (ret == 0 && page->next != NULL)
		search_zone(page->next, ptr);
	*/
}

void	free(void *ptr)
{
	if (ptr != NULL)
		search_zone(&g_page, ptr);
}


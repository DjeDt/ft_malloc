/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 20:30:59 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/09 18:48:14 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	rebuilt_area_chunk(t_chunk **chunk)
{
/*
    ___<__<__
 __/    __    \__
|  |   | N|-->|  |
|__|<--|P_|   |__|
    \-->-->--/
*/
	if ((*chunk)->prev)
		(*chunk)->prev->next = (*chunk)->next;
	if ((*chunk)->next)
		(*chunk)->next->prev = (*chunk)->prev;
}

void	push_chunk_to_bin(t_chunk **bin, t_chunk **chunk)
{
	t_chunk *tmp;

	if ((*bin) == NULL)
	{
		rebuilt_area_chunk(chunk);
		(*chunk)->statut = FREE;
		(*bin) = (*chunk);
	}
	else
	{
		tmp = (*bin);
		while (tmp->next != NULL && (tmp->size <= (*chunk)->size))
			tmp->next = tmp;
		rebuilt_area_chunk(chunk);

		if (tmp->next->next)
			tmp->next->next->prev = (*chunk);

		(*chunk)->prev = tmp;
		(*chunk)->next = tmp->next;
		(*chunk)->statut = FREE;
		tmp->next = (*chunk);
	}
}

int		search_in_page(t_chunk **lst, void *ptr)
{
	t_chunk	*tmp;

	if ((*lst) == NULL)
		return (ERROR);
	tmp = (*lst);
	while (tmp != NULL)
	{
		printf("[while] tmp->data : %p | ptr : %p\n", tmp->data, ptr);
		if (tmp->data == ptr)
		{
			push_chunk_to_bin(&g_page.bin, &tmp);
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	return (NOPE);
}

int		search_smaller_one(void *ptr, t_area **area)
{
	t_area	*a_tmp;

	a_tmp = (*area);
	while (a_tmp != NULL)
	{
		if (search_in_page(&a_tmp->chunk, ptr) == SUCCESS)
			return (SUCCESS);
		a_tmp = a_tmp->next;
	}
	return (NOPE);
}

int		search_large_one(void *ptr)
{
	(void)ptr;
	return (NOPE);
}

void	search_for_chunk(void *ptr)
{
	if (search_smaller_one(ptr, &g_page.small) != SUCCESS)
	{
		if (search_smaller_one(ptr, &g_page.medium) != SUCCESS)
			search_large_one(ptr);
	}
}

void	free(void *ptr)
{
	if (ptr == NULL)
		return ;
	printf("[free 1] %p\n", ptr);
	search_for_chunk(ptr);
	printf("\n\nPRINT ALLOCATED CHUNK PAGE BIN\n");
	print_allocated_chunk(&g_page.bin);
	printf("\n\nPRINT ALLOCATED CHUNK PAGE SMALL\n");
	print_allocated_chunk(&g_page.small->chunk);
}

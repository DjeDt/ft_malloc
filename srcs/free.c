/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 20:30:59 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/16 16:43:44 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	rebuilt_area_chunk(t_chunk **chunk, t_chunk **head)
{
	if ((*chunk)->prev)
		(*chunk)->prev->next = (*chunk)->next;
	else
		(*head) = (*chunk)->next;
	if ((*chunk)->next)
		(*chunk)->next->prev = (*chunk)->prev;
	(*chunk)->next = NULL;
	(*chunk)->prev = NULL;
	(*chunk)->statut = FREE;
}

void	extract_and_push(t_chunk **bin, t_chunk **chunk)
{
	t_chunk *tmp;

	if ((*bin) == NULL)
	{
		rebuilt_area_chunk(chunk, bin);
		(*bin) = (*chunk);
	}
	else
	{
		rebuilt_area_chunk(chunk, bin);
		tmp = (*bin);
		while ((tmp->next != NULL) && (tmp->next->size <= (*chunk)->size))
			tmp = tmp->next;
		(*chunk)->prev = tmp;
		if (tmp->next)
		{
			(*chunk)->next = tmp->next->next;
			tmp->next->prev = (*chunk);
		}
		else
			(*chunk)->next = NULL;
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
		if (tmp->data == ptr)
		{
			extract_and_push(&g_page.bin, &tmp);
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

int		search_large_one(void *ptr, t_area **area)
{
	t_area *a_tmp;
	t_area *prev;

	a_tmp = (*area);
	while (a_tmp != NULL)
	{
		if (a_tmp->map == ptr)
		{
			prev->next = a_tmp->next;
			munmap(a_tmp, a_tmp->size_max);
			return (SUCCESS);
		}
		prev = a_tmp;
		a_tmp = a_tmp->next;
	}
	return (NOPE);
}

void	free(void *ptr)
{
	if (ptr == NULL)
		return ;
	if (search_smaller_one(ptr, &g_page.small) != SUCCESS)
	{
		if (search_smaller_one(ptr, &g_page.medium) != SUCCESS)
			search_large_one(ptr, &g_page.large);
	}
}

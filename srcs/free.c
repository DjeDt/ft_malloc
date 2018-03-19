/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 20:30:59 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/19 19:22:14 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
**	Unused since i removed bin linked list
*/
void	rebuilt_area_chunk(t_chunk **chunk)
{
	if ((*chunk)->prev)
		(*chunk)->prev->next = (*chunk)->next;
	if ((*chunk)->next)
		(*chunk)->next->prev = (*chunk)->prev;

	(*chunk)->next = NULL;
	(*chunk)->prev = NULL;
	(*chunk)->statut = FREE;
}

/*
**	Unused since i removed bin linked list
*/
void	extract_and_push(t_chunk **bin, t_chunk **chunk)
{
	t_chunk *tmp;

	rebuilt_area_chunk(chunk);
	if ((*bin) == NULL)
		(*bin) = (*chunk);
	else
	{
		tmp = (*bin);
		while (tmp->next != NULL)
		{
			if (tmp->size <= (*chunk)->size)
				break ;
			tmp = tmp->next;
		}

		tmp->next = (*chunk);
		if (tmp->next == NULL)
		{
			(*chunk)->prev = tmp;
			return ;
		}
		(*chunk)->prev = tmp;
		if (tmp->next)
		{
			(*chunk)->next = tmp->next->next;
			tmp->next->prev = (*chunk);
		}
		else
			(*chunk)->next = NULL;
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
			/*
			**	Unused since i removed double linked list :
			** extract_and_push(&g_page.bin, &tmp);
			*/
			tmp->statut = FREE;
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
	t_area	*tmp;
	t_area	*prev;

	tmp = (*area);
	prev = NULL;
	while (tmp != NULL && (tmp->map != ptr))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return (NOPE);
	if ((prev == NULL) && (tmp->next == NULL))
	{
		munmap(tmp, tmp->size_max);
		(*area) = NULL;
	}
	else
	{
		prev->next = tmp->next;
		munmap(tmp, tmp->size_max);
	}
	return (SUCCESS);
}

void	free(void *ptr)
{
	if (ptr == NULL)
		return ;
	if (search_smaller_one(ptr, &g_page.small) != SUCCESS)
		if (search_smaller_one(ptr, &g_page.medium) != SUCCESS)
			search_large_one(ptr, &g_page.large);
}

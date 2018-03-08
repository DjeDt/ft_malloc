/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 20:30:59 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/08 21:14:04 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	assign_to_bin(t_chunk **head, t_chunk **new)
{
	t_chunk *swap;

	swap = (*head)->next;
	(*new)->previous = NULL;
	(*new)->statut = FREE;
	(*new)->next = swap;
	(*head)->next = (*new);
}

void	move_chunk_to_bin(t_chunk **bin, t_chunk **chunk)
{
	t_chunk *tmp;

	if ((*bin) == NULL)
	{
		ft_putendl("test1");
		(*bin) = (*chunk);
		(*bin)->next = NULL;
		(*bin)->statut = FREE;
		(*bin)->previous = NULL;
	}
	else
	{
		ft_putendl("test2");
		tmp = (*bin);
		while (tmp->next != NULL)
			tmp = tmp->next;
		assign_to_bin(&tmp->next, chunk);
	}
}

int		search_in_page(t_chunk **lst, void *ptr)
{
	t_chunk	*tmp;

	tmp = (*lst);
	if (tmp == NULL)
		return (ERROR);
	while (tmp)
	{
		if (tmp == (ptr - HEADER_SIZE))
		{
			ft_putendl("found");
			move_chunk_to_bin(&g_page.bin, &tmp);
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
	search_for_chunk(ptr);
	print_allocated_chunk(&g_page.bin);
}

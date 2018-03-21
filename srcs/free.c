/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 20:30:59 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/21 19:31:47 by ddinaut          ###   ########.fr       */
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

static int	search_large(t_area *area, void *ptr)
{
	t_area	*save;
	t_area	*prev;

	prev = NULL;
	save = area;
	ft_putendl("test1");
	while (save != NULL)
	{
		if (save->map == ptr)
		{
			if (prev != NULL)
				prev->next = save->next;
			else
				area = save->next;
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

	save = list;
	ft_putendl("test2");
	while (save != NULL)
	{
		ft_putendl("test22");
		if (save->data == ptr)
		{
			ft_putendl("test34");
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
	ft_putendl("test3");
	while (save != NULL)
	{
		if (search_for_chunk(save->chunk, ptr) == SUCCESS)
			return (SUCCESS);
		save = save->next;
	}
	return (NOPE);
}

void	free(void *ptr)
{
	if (ptr == NULL)
		return ;
	ft_putstr("[free] : ");
	int ret; /* debug */

	if ((ret = search_smaller(g_page.small, ptr)) != SUCCESS)
		if ((ret = search_smaller(g_page.medium, ptr)) != SUCCESS)
			ret = search_large(g_page.large, ptr);

	if (ret == SUCCESS)
		ft_putendl("success");
	else
		ft_putendl("nope");
}

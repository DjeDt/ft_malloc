/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 20:30:59 by ddinaut           #+#    #+#             */
/*   Updated: 2018/04/09 18:30:19 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	search_large(t_area *area, void *ptr)
{
	t_area	*save;
	t_area	*prev;
	int ret; /* debug value */

	prev = NULL;
	save = area;
	while (save != NULL)
	{
		if (save + AREA_SIZE == ptr)
		{
			if (prev != NULL)
				prev->next = save->next;
			else
				area = save->next;
			ret = munmap(save, save->size_max + AREA_SIZE);
			if (DEBUG == 1)
			{
				ft_putstr("[free] munmap ret value = ");
				ft_putnbr(ret);
				ft_putchar('\n');
			}

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
	while (save != NULL)
	{
		if (save + HEADER_SIZE == ptr)
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

void	free(void *ptr)
{
	if (ptr == NULL)
		return ;

	int ret = 0; /* debug */
	if (DEBUG == 1)
	{
		ft_putstr("[free] : ");
		ft_putnbr(hmt++);
		ft_putchar('\n');
	}

	if ((ret = search_smaller(g_page.small, ptr)) != SUCCESS)
		if ((ret = search_smaller(g_page.medium, ptr)) != SUCCESS)
			ret = search_large(g_page.large, ptr);

	if (DEBUG == 1)
	{
		if (ret == SUCCESS)
			ft_putendl("success");
		else
			ft_putendl("nope");
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_area.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:49:41 by ddinaut           #+#    #+#             */
/*   Updated: 2018/04/20 11:41:46 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_area	*create_large_area(size_t size)
{
	t_area	*new;

	new = mmap(NULL, size + AREA_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (new == MAP_FAILED)
	{
		ft_putendl_fd("allocation error. not enought space left.", 2);
		return (NULL);
	}
	new->size_used = size + AREA_SIZE;
	new->size_max = size + AREA_SIZE;
	new->chunk = NULL;
	new->next = NULL;
	return (new);
}

t_area	*create_new_area(size_t size, t_area *prev)
{
	size_t	total;
	t_area	*new;

	total = size * getpagesize();
	new = mmap(NULL, total + AREA_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (new == MAP_FAILED)
	{
		ft_putendl_fd("allocation error. not enought space left.", 2);
		return (NULL);
	}
	new->size_used = AREA_SIZE;
	new->size_max = total + AREA_SIZE;
	new->chunk = NULL;
	new->next = NULL;
	if (prev != NULL)
		prev->next = new;
	return (new);
}

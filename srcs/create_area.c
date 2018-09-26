/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_area.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:49:41 by ddinaut           #+#    #+#             */
/*   Updated: 2018/09/26 17:05:57 by ddinaut          ###   ########.fr       */
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

	if (ENABLE_DEBUG == ENABLE)
	{
		ft_putstr("create large arena : ");
		ft_putstr("size is "); ft_putnbr(size); ft_putstr(" octets");
		ft_putstr("size max is equal to : "); ft_putnbr(size + AREA_SIZE);
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

	(void)size;
	total = 100 * getpagesize();

	if (ENABLE_DEBUG == ENABLE)
	{
		ft_putstr("create_new_area : size = ");
		ft_putnbr(total);
		ft_putchar('\n');
	}

	new = mmap(NULL, total + AREA_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (new == MAP_FAILED)
	{
		ft_putendl_fd("allocation error. not enought space left.", 2);
		return (NULL);
	}
	new->size_used = AREA_SIZE;
	new->size_max = total;
	new->chunk = NULL;
	new->next = NULL;

	if (ENABLE_DEBUG == ENABLE)
	{
		ft_putstr("page size_used = ");
		ft_putnbr(new->size_used);
		ft_putstr("\nsize_max = ");
		ft_putnbr(new->size_max);
		ft_putchar('\n');
	}

	if (prev != NULL)
		prev->next = new;
	return (new);
}

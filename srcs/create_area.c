/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_area.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:49:41 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/04 18:30:56 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t	get_total_allocation(size_t area_size, size_t get_page_size)
{
	size_t p_num;
	size_t a_num;

	p_num = 0;
	a_num = 0;
	while (a_num < 100)
		a_num = (++p_num) * get_page_size / area_size;
	return (p_num);
}

t_area	*create_large_area(size_t size)
{
	size_t	total;
	t_area	*new;

	total = size + AREA_SIZE;
	new = mmap(NULL, total, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (new == MAP_FAILED)
	{
		ft_putendl_fd("allocation error. not enought space left.", 2);
		return (NULL);
	}
	new->size_used = total;
	new->size_max = total;
	new->chunk = NULL;
	new->next = NULL;
	return (new);
}

t_area	*create_new_area(size_t size, t_area *prev)
{
	size_t	total;
	size_t	page_len;
	size_t	page_num;
	t_area	*new;

	page_len = getpagesize();
	page_num = get_total_allocation(page_len, size);
	total = (page_num * page_len) + AREA_SIZE;
	new = mmap(NULL, total, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (new == MAP_FAILED)
	{
		ft_putendl_fd("allocation error. not enought space left.", 2);
		return (NULL);
	}
	new->size_used = AREA_SIZE;
	new->size_max = total;
	new->chunk = NULL;
	new->next = NULL;
	if (prev != NULL)
		prev->next = new;
	return (new);
}

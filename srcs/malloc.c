/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:39:27 by ddinaut           #+#    #+#             */
/*   Updated: 2018/04/10 18:03:33 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	print_area(void)
{
	int count, count2;
	t_area	*area;
	t_chunk *chunk;

	count = 0;
	count2 = 0;
	area = g_page.small;
	while (area != NULL)
	{
		chunk = area->chunk;
		while (chunk != NULL)
		{
			if (chunk->statut == USED)
				count2++;
			chunk = chunk->next;
		}
		area = area->next;
		count++;
	}
	ft_putstr("SMALL PAGE = ");
	ft_putnbr(count);
	ft_putstr(" NB CHUNK = ");
	ft_putnbr(count2);
	ft_putchar('\n');

	count = 0;
	count2 = 0;
	area = g_page.medium;
	while (area != NULL)
	{
		chunk = area->chunk;
		while (chunk != NULL)
		{
			if (chunk->statut == USED)
				count2++;
			chunk = chunk->next;
		}
		area = area->next;
		count++;
	}
	ft_putstr("MEDIUM PAGE = ");
	ft_putnbr(count);
	ft_putstr(" NB CHUNK = ");
	ft_putnbr(count2);
	ft_putchar('\n');

	count = 0;
	area = g_page.large;
	while (area != NULL)
	{
		count++;
		area = area->next;
	}
	ft_putstr("LARGE PAGE = ");
	ft_putnbr(count);
	ft_putstr("\n\n");
}

void	*malloc(size_t size)
{
	void	*ret;

	size = ALIGN(size + (size > MEDIUM_SIZE ? AREA_SIZE : HEADER_SIZE));
	if (DEBUG == 1)
	{
		ft_putstr("[malloc : ");
		ft_putnbr(hmt++);
		ft_putstr("] | size = ");
		ft_putnbr(size);
		ft_putstr("]");
	}

	ret = push_chunk_to_area(size);

	if (DEBUG == 1)
	{
		ft_putstr(" addr = ");
		ft_putaddr(ret);
		ft_putstr(" ]\n");
	}
	print_area();
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 15:47:38 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/01 17:25:23 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	print_info(void *addr, void *next, size_t size)
{
	if (addr)
	{
		ft_putaddr(addr);
		ft_putstr(" data : ");
		ft_putaddr(addr + HEADER_SIZE);
	}
	if (next)
	{
		ft_putstr(" -> next-chunk -> ");
		ft_putaddr(next);
	}
	ft_putstr(" : ");
	ft_putnbr(size);
	ft_putendl(" octets");
}

void	print_larger(t_area *tmp)
{
	t_area	*tmp_lrg;

	ft_putstr("LARGE: ");
	if (tmp == NULL)
	{
		ft_putendl("Empty large area");
		return ;
	}
	tmp_lrg = tmp;
	ft_putaddr(tmp_lrg);
	ft_putchar('\n');
	while (tmp_lrg != NULL)
	{
		print_info(tmp_lrg, tmp_lrg + tmp_lrg->size_used, tmp_lrg->size_used);
		tmp_lrg = tmp_lrg->next;
	}
}

void	print_medium(t_area *tmp)
{
	t_area	*tmp_area;
	t_chunk	*tmp_chunk;

	tmp_area = tmp;
	ft_putstr("MEDIUM: ");
	if (tmp_area == NULL)
	{
		ft_putendl("Empty medium area");
		return ;
	}
	ft_putaddr(tmp_area);
	ft_putchar('\n');
	while (tmp_area != NULL)
	{
		tmp_chunk = tmp_area->chunk;
		while (tmp_chunk != NULL)
		{
			print_info(tmp_chunk, tmp_chunk + tmp_chunk->size, tmp_chunk->size);
			tmp_chunk = tmp_chunk->next;
		}
		tmp_area = tmp_area->next;
	}
}

void	print_tiny(t_area *tmp)
{
	t_area	*tmp_area;
	t_chunk	*tmp_chunk;

	tmp_area = tmp;
	ft_putstr("TINY: ");
	if (tmp_area == NULL)
	{
		ft_putendl("Empty tiny area\n");
		return ;
	}
	ft_putstr("area main addr : ");
	ft_putaddr(tmp_area);
	ft_putchar('\n');
	while (tmp_area != NULL)
	{
		tmp_chunk = tmp_area->chunk;
		while (tmp_chunk != NULL)
		{
			ft_putstr("tiny chunk : ");
			print_info(tmp_chunk, tmp_chunk + tmp_chunk->size, tmp_chunk->size);
			tmp_chunk = tmp_chunk->next;
		}
		tmp_area = tmp_area->next;
	}
}

void	show_alloc_mem(void)
{
	t_pages tmp_page;

	tmp_page = g_page;
	print_tiny(tmp_page.small);
	print_medium(tmp_page.medium);
	print_larger(tmp_page.large);
	return ;
}

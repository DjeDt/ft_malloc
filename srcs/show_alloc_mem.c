/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 15:47:38 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/05 16:47:30 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	print_info(void *addr, size_t size)
{
	if (addr)
	{
		ft_putaddr(addr);
		ft_putstr(" data : ");
		ft_putaddr((char*)addr + HEADER_SIZE);
	}
	ft_putstr(" : ");
	ft_putnbr(size);
	ft_putendl(" octets");
}

void	print_larger(t_area *tmp)
{
	t_area	*tmp_lrg;

	ft_putstr("LARGE: ");
	tmp_lrg = tmp;
	ft_putaddr(tmp_lrg);
	ft_putchar('\n');
	while (tmp_lrg != NULL)
	{
		print_info(tmp_lrg, tmp_lrg->size_used);
		tmp_lrg = tmp_lrg->next;
	}
}

void	print_medium(t_area *tmp)
{
	t_area	*tmp_area;
	t_chunk	*tmp_chunk;

	tmp_area = tmp;
	ft_putstr("MEDIUM: ");
	ft_putaddr(tmp_area);
	ft_putchar('\n');
	while (tmp_area != NULL)
	{
		tmp_chunk = tmp_area->chunk;
		while (tmp_chunk != NULL)
		{
			ft_putstr("statut = ");
			if (tmp_chunk->statut == FREE)
				ft_putstr("free | ");
			else
				ft_putstr("used | ");
			print_info(tmp_chunk, tmp_chunk->size);
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
	ft_putstr("area main addr : ");
	ft_putaddr(tmp_area);
	ft_putchar('\n');
	while (tmp_area != NULL)
	{
		tmp_chunk = tmp_area->chunk;
		while (tmp_chunk != NULL)
		{
			ft_putstr("statut = ");
			if (tmp_chunk->statut == FREE)
				ft_putstr("free | ");
			else
				ft_putstr("used | ");
			print_info(tmp_chunk, tmp_chunk->size);
			tmp_chunk = tmp_chunk->next;
		}
		tmp_area = tmp_area->next;
	}
}

void	show_alloc_mem(void)
{
	print_tiny(g_page.small);
	print_medium(g_page.medium);
	print_larger(g_page.large);
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 15:47:38 by ddinaut           #+#    #+#             */
/*   Updated: 2018/09/24 17:36:57 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	print_larger(t_area *tmp)
{
	ft_printf("LARGE: \n");
	(void)tmp;
}

void	print_medium(t_area *tmp)
{
	t_area *tmp_area;
	t_chunk *tmp_chunk;

	tmp_area = tmp;
	ft_printf("MEDIUM: \n");
	if (tmp_area == NULL)
		ft_printf("empty medium area\n");
		return ;
	while (tmp_area != NULL)
	{
		tmp_chunk = tmp_area->chunk;
		while (tmp_chunk->next != NULL)
		{
			ft_printf("%p - %p : %lld octets", tmp_chunk, tmp_chunk + tmp_chunk->size, tmp_chunk->size );
			tmp_chunk = tmp_chunk->next;
		}
		tmp_area = tmp_area->next;
	}
}

void	print_tiny(t_area *tmp)
{
	t_area *tmp_area;
	t_chunk *tmp_chunk;

	tmp_area = tmp;
	ft_putstr("TINY: ");
	ft_putaddr(tmp_area);
	ft_putchar('\n');
	if (tmp_area == NULL)
	{
		ft_printf("empty tiny area\n");
		return ;
	}
	while (tmp_area != NULL)
	{
		tmp_chunk = tmp_area->chunk;
		while (tmp_chunk != NULL)
		{
			ft_putaddr(tmp_chunk);
			ft_putstr(" - ");
			ft_putaddr(tmp_chunk + tmp->chunk->size);
			ft_putstr(" ");
			ft_putnbr(tmp_chunk->size);
			ft_putendl(" octets");
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
//	print_medium(tmp_page.medium);
//	print_larger(tmp_page.large);
	return ;
}

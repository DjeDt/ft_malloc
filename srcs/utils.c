/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 17:23:57 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/21 17:28:56 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

# define HEX "0123456789abcdef"
void		ft_puthex(unsigned long l)
{
	if (l >= 16)
	{
		ft_puthex(l / 16);
		ft_puthex(l % 16);
	}
	else
		ft_putchar(HEX[l]);
}

void		ft_putaddr(void *ptr)
{
	ft_putstr("0x");
	ft_puthex((unsigned long)ptr);
}

void	count_zone(t_area **area)
{
	size_t	count;
	t_area *tmp;

	count = 0;
	tmp = (*area);
	while (tmp != NULL)
	{
		count++;
		tmp = tmp->next;
	}
	ft_putstr("there is ");
	ft_putnbr(count);
	ft_putendl(" area");
}

void	print_all(t_chunk **chunk)
{
	int		count;
	t_chunk *tmp;

	count = 0;
	tmp = (*chunk);
	while (tmp != NULL)
	{
		printf("[chunk %d] size = %zu | statut = %d\n", count, tmp->size, tmp->statut);
		count++;
		tmp = tmp->next;
	}
}


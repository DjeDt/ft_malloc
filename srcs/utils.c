/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 17:23:57 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/04 18:06:15 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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

void		ft_puthex_fd(unsigned long l, int fd)
{
	if (l >= 16)
	{
		ft_puthex_fd(l / 16, fd);
		ft_puthex_fd(l % 16, fd);
	}
	else
		ft_putchar_fd(HEX[l], fd);
}

void		ft_putaddr(void *ptr)
{
	ft_putstr("0x");
	ft_puthex((unsigned long)ptr);
}

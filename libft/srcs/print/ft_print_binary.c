/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_binary.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 17:36:29 by ddinaut           #+#    #+#             */
/*   Updated: 2017/05/11 19:14:52 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_binary(unsigned int n)
{
	int				count;
	unsigned int	bit;
	unsigned int	mask;

	bit = 0;
	mask = 1;
	count = -1;
	while (++count < 32)
	{
		bit = (n & mask) >> count;
		ft_putnbr(bit);
		mask <<= 1;
	}
}

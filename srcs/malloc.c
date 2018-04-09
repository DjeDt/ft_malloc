/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:39:27 by ddinaut           #+#    #+#             */
/*   Updated: 2018/04/09 18:50:23 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*malloc(size_t size)
{
	void	*ret;

	size = ALIGN(size);

	if (DEBUG == 1)
	{
		ft_putstr("[malloc] : ");
		ft_putnbr(hmt++);
		ft_putstr(" | size = ");
		ft_putnbr(size);
		ft_putchar('\n');
	}
	ret = push_chunk_to_area(size);
	return (ret);
}

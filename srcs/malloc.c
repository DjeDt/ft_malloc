/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:39:27 by ddinaut           #+#    #+#             */
/*   Updated: 2018/09/26 18:09:53 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t	align_size(size_t size)
{

//	v3
/*	size--;
    size |= size >> 1;
    size |= size >> 2;
    size |= size >> 4;
    size |= size >> 8;
    size |= size >> 16;
    size++;
*/

// v2
//	size += (size & 1);

// v1
//	size = ALIGN(size + (size > MEDIUM_SIZE ? AREA_SIZE : HEADER_SIZE));

	// v4
	size = (size + 1) & ~1;
	return (size);
}

void	*malloc(size_t size)
{
	void	*ret;


	if (ENABLE_DEBUG == ENABLE)
	{
		ft_putstr("size asked : ");
		ft_putnbr(size);
		ft_putstr("     ");
	}

	size = align_size(size + (size > MEDIUM_SIZE ? AREA_SIZE : HEADER_SIZE));

	if (ENABLE_DEBUG == ENABLE)
	{
		ft_putstr("size aligned : ");
		ft_putnbr(size);
		ft_putchar('\n');
	}

	if (size <= MEDIUM_SIZE)
		ret = manage_small_or_medium(size);
	else
		ret = manage_large(&g_page.large, size);

	if (ENABLE_DEBUG == ENABLE)
		ft_putchar('\n');
	return (ret);
}

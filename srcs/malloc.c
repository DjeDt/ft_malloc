/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:39:27 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/03 15:58:52 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t	align_size(size_t size)
{
	size = (size + 1) & ~1;
	return (size);
}

void	*malloc(size_t size)
{
	void	*ret;

	size = align_size(size);
	if (size <= MEDIUM_SIZE)
	{
//		ft_putendl("<= medium");
		ret = manage_small_or_medium(size);
	}
	else
	{
//		ft_putendl("large");
		ret = manage_large(size, &g_page.large);
	}
	/* ft_putstr("address returned : "); */
	/* ft_putaddr(ret); */
	/* ft_putchar('\n'); */
	return (ret);
}

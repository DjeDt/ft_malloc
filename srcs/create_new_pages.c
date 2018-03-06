/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_pages.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 13:55:39 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/06 16:13:22 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*create_new_pages(size_t size, int zone_size)
{
	void	*new;
	size_t	total;

	total = size * zone_size * getpagesize();
	new = mmap(NULL, total, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (new == MAP_FAILED)
	{
		ft_putstr_fd("fatal error during allocation, not enough space left\n", 2);
		return (NULL);
	}
	return (new);
}

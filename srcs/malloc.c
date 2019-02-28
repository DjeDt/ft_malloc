/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:39:27 by ddinaut           #+#    #+#             */
/*   Updated: 2019/02/28 18:02:25 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t	align_size(size_t size, size_t align)
{
	if (size % align != 0)
		size += align - (size % align);
	return (size);
}

void	*malloc_protected(size_t size)
{
	void	*ret;

	compare_checksum();
	if (size <= MEDIUM_SIZE)
	{
		size = align_size(size, MEM_ALIGN);
		ret = manage_small_or_medium(size);
	}
	else
	{
		size = align_size(size, MEM_ALIGN);
		size = align_size(size, getpagesize());
		ret = manage_large(size, &g_page.large);
	}
	generate_new_checksum();
	return (ret);
}

void	*malloc(size_t size)
{
	void *ret;

	thread_protection_lock();
	ret = malloc_protected(size);
	thread_protection_unlock();
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:39:27 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/17 18:04:56 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t	align_size(size_t size)
{
	if (size % MEM_ALIGN != 0)
		size += MEM_ALIGN - (size % MEM_ALIGN);
	return (size);
}

void	*malloc(size_t size)
{
	void	*ret;

	thread_protection_lock();
	compare_checksum();
	size = align_size(size);
	if (size <= MEDIUM_SIZE)
		ret = manage_small_or_medium(size);
	else
		ret = manage_large(size, &g_page.large);
	generate_new_checksum();
	thread_protection_unlock();
	return (ret);
}

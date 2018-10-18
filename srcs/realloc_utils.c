/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:39:46 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/18 12:24:25 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_chunk		*larger_chunk_found(t_chunk *save, size_t aligned)
{
	thread_protection_lock();
	save->size = aligned;
	generate_new_checksum();
	thread_protection_unlock();
	return (save);
}

void		*realloc_new_chunk(t_chunk *save, void *ptr, size_t size)
{
	void *ret;

	ret = malloc(size);
	thread_protection_lock();
	ft_memcpy(ret, ptr, save->size);
	thread_protection_unlock();
	free(save);
	return (ret);
}

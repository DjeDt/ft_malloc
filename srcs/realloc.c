/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:56:42 by ddinaut           #+#    #+#             */
/*   Updated: 2019/03/01 13:28:37 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_chunk     *larger_chunk_found(t_chunk *save, size_t aligned)
{
	save->size = aligned;
	generate_new_checksum();
	return (save);
}

void        *realloc_new_chunk(t_chunk *save, void *ptr, size_t size)
{
	void *ret;

	ret = malloc_protected(size);
	ft_memcpy(ret, ptr, save->size);
	free_protected(ptr);
	return (ret);
}

static void		*check_area(void *ptr, size_t size)
{
	size_t	align;
	void	*ret;

	ret = NULL;
	compare_checksum();
	align = align_size(size, MEM_ALIGN);
	if ((ret = search_tiny_chunk(ptr, size, align)) != NULL)
		return (ret);
	if ((ret = search_medium_chunk(ptr, size, align)) != NULL)
		return (ret);
	if ((ret = search_large_chunk(ptr, size)) != NULL)
		return (ret);
	return (NULL);
}

void			*realloc_protected(void *ptr, size_t size)
{
	if (ptr == NULL)
		return (malloc_protected(size));
	else if (size == 0)
		free_protected(ptr);
	else
		return (check_area(ptr, size));
	return (ptr);
}

void			*realloc(void *ptr, size_t size)
{
	void *ret;

	thread_protection_lock();
	ret = realloc_protected(ptr, size);
	thread_protection_unlock();
	return (ret);
}

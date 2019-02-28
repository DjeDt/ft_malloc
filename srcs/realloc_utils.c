/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:39:46 by ddinaut           #+#    #+#             */
/*   Updated: 2019/02/28 12:28:29 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_chunk		*larger_chunk_found(t_chunk *save, size_t aligned)
{
	save->size = aligned;
	generate_new_checksum();
   	return (save);
}

void		*realloc_new_chunk(t_chunk *save, void *ptr, size_t size)
{
	void *ret;

	ret = malloc_protected(size);
	ft_memcpy(ret, ptr, save->size);
	free_protected(save);
	return (ret);
}

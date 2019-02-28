/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:31:48 by ddinaut           #+#    #+#             */
/*   Updated: 2019/02/28 17:32:35 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*calloc_protected(size_t count, size_t size)
{
	size_t	total;
	void	*new;

	total = count * size;
	new = malloc_protected(total);
	ft_memset(new, '\0', total);
	return (new);
}

void	*calloc(size_t count, size_t size)
{
	void *ret;

	thread_protection_lock();
	ret = calloc_protected(count, size);
	thread_protection_unlock();
	return (ret);
}

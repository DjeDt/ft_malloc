/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:39:27 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/05 15:31:50 by ddinaut          ###   ########.fr       */
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

	thread_protection_lock();
	if (ENABLE_CHECKSUM == ENABLE && generate_checksum() != g_page.cheksum)
		ft_putendl_fd("error, hash differs, corrupted data", STDERR_FILENO);
	size = align_size(size);
	if (size <= MEDIUM_SIZE)
		ret = manage_small_or_medium(size);
	else
		ret = manage_large(size, &g_page.large);
	if (ENABLE_CHECKSUM == ENABLE)
		g_page.cheksum = generate_checksum();
	thread_protection_unlock();
	return (ret);
}

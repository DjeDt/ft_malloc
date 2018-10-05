/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:31:48 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/05 14:54:41 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*calloc(size_t count, size_t size)
{
	size_t	total;
	void	*new;

	total = count * size;
	new = malloc(total);
	if (pthread_mutex_lock(&g_thread) != 0)
		ft_putendl_fd("error, can't lock mutex", STDERR_FILENO);
	ft_memset(new, '\0', total);
	if (ENABLE_CHECKSUM == ENABLE)
		g_page.cheksum = generate_checksum();
	if (pthread_mutex_unlock(&g_thread) != 0)
		ft_putendl_fd("error, can't unlock mutex", STDERR_FILENO);
	return (new);
}

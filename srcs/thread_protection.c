/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_protection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 14:58:10 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/05 15:00:39 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	thread_protection_lock(void)
{
	if (ENABLE_THREAD_PROTECT == ENABLE)
	{
		if (pthread_mutex_lock(&g_thread) != 0)
			ft_putendl_fd("error, can't lock mutex", STDERR_FILENO);
	}
}

void	thread_protection_unlock(void)
{
	if (ENABLE_THREAD_PROTECT == ENABLE)
	{
		if (pthread_mutex_unlock(&g_thread) != 0)
			ft_putendl_fd("error, can't unlock mutex", STDERR_FILENO);
	}
}

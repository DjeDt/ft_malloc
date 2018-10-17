/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:31:48 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/17 15:55:52 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*calloc(size_t count, size_t size)
{
	size_t	total;
	void	*new;

	total = count * size;
	new = malloc(total);
	thread_protection_lock();
	new = ft_memset(new, '\0', total);
	thread_protection_unlock();
	return (new);
}

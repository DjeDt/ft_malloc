/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:31:48 by ddinaut           #+#    #+#             */
/*   Updated: 2018/10/04 19:59:56 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*calloc(size_t count, size_t size)
{
	size_t	total;
	void	*new;

	total = count * size;
	new = malloc(total);
	ft_memset(new, '\0', total);
	if (ENABLE_CHECKSUM == ENABLE)
		g_page.cheksum = generate_checksum();
	return (new);
}

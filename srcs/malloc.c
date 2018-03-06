/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:39:27 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/06 17:21:29 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*malloc(size_t size)
{
	void	*ret;

	if (!size)
	{
		ft_putendl("return null");
		return (NULL);
	}
	if (size < TINY_SIZE)
		ret = add_to_tiny(size, &g_page.tiny);
	else if (size < MEDIUM_SIZE)
		ret = add_to_medium(size, &g_page.medium);
	else
		ret = add_to_large(size, &g_page.large);
	return (ret + HEADER_SIZE);
}
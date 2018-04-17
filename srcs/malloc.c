/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:39:27 by ddinaut           #+#    #+#             */
/*   Updated: 2018/04/17 12:30:40 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*malloc(size_t size)
{
	void	*ret;

	size = ALIGN(size + (size > MEDIUM_SIZE ? AREA_SIZE : HEADER_SIZE));
	ret = push_chunk_to_area(size);
	return (ret);
}

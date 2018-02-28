/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 21:24:57 by ddinaut           #+#    #+#             */
/*   Updated: 2016/11/16 19:44:20 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmp;
	unsigned char	cara;

	tmp = (unsigned char*)s;
	cara = (unsigned char)c;
	while (n--)
	{
		if ((unsigned char)*tmp == (unsigned char)cara)
			return ((unsigned char*)tmp);
		tmp++;
	}
	return (NULL);
}

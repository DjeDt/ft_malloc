/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 20:03:17 by ddinaut           #+#    #+#             */
/*   Updated: 2016/11/16 19:45:10 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;

	s1 = (unsigned char*)dst;
	s2 = (unsigned char*)src;
	i = 0;
	if (s2 < s1)
	{
		s1 += len - 1;
		s2 += len - 1;
		while (len-- > 0)
			*s1-- = *s2--;
		return (dst);
	}
	else
	{
		while (i < len)
		{
			s1[i] = s2[i];
			i++;
		}
		return (dst);
	}
}

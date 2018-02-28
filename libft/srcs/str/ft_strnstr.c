/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 20:18:04 by ddinaut           #+#    #+#             */
/*   Updated: 2016/11/16 19:51:23 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (!(little[i]))
		return ((char*)big);
	while (i < len && big[i])
	{
		while (big[i + j] == little[j] && (i + 1 <= len))
		{
			if (ft_strlen(little) + i > len)
				return (NULL);
			if (little[j + 1] == '\0' && (i <= len))
				return ((char*)big + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

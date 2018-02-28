/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 20:18:45 by ddinaut           #+#    #+#             */
/*   Updated: 2016/11/16 19:51:39 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ret;

	i = ft_strlen(s);
	if (s[0] == '\0')
		return (NULL);
	if (s[i] == c)
		return ((char*)&s[i]);
	while (i >= 0)
	{
		if (s[i] == c)
		{
			ret = (char*)&s[i];
			return (ret);
		}
		i--;
	}
	return (NULL);
}

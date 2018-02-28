/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 20:10:03 by ddinaut           #+#    #+#             */
/*   Updated: 2016/12/23 13:59:33 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	ft_strchr :
**	-> Returns a pointer to the first occurrence of the char c in the string s.
*/

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ret;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] == c)
			{
				ret = (char*)&s[i];
				return (ret);
			}
			i++;
		}
		if (s[i] == c)
			return ((char*)&s[i]);
	}
	return (NULL);
}

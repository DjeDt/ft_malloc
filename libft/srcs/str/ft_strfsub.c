/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfsub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 15:13:24 by ddinaut           #+#    #+#             */
/*   Updated: 2018/01/18 14:36:14 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strfsub(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ret;

	i = 0;
	ret = NULL;
	if (s != NULL)
	{
		if (!(ret = (char*)malloc(sizeof(char) * (len + 1))))
			return (NULL);
		while (i < len)
		{
			ret[i] = s[start];
			i++;
			start++;
		}
		ret[i] = '\0';
		ft_strdel(&s);
	}
	return (ret);
}

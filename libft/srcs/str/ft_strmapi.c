/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 02:42:57 by ddinaut           #+#    #+#             */
/*   Updated: 2016/11/16 19:58:49 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ret;

	i = 0;
	ret = NULL;
	if (s)
	{
		if (!(ret = ft_strdup((char*)s)))
			return (NULL);
		while (ret[i])
		{
			ret[i] = (f)(i, ret[i]);
			i++;
		}
		ret[i] = '\0';
	}
	return (ret);
}

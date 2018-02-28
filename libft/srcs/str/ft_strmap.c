/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 02:36:38 by ddinaut           #+#    #+#             */
/*   Updated: 2016/11/16 19:58:30 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	char	*ret;

	i = 0;
	ret = NULL;
	if (s)
	{
		if (!(ret = ft_strdup((char*)s)))
			return (NULL);
		while (ret[i])
		{
			ret[i] = (f)(ret[i]);
			i++;
		}
		ret[i] = '\0';
	}
	return (ret);
}

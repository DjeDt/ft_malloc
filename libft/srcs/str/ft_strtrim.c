/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 04:44:04 by ddinaut           #+#    #+#             */
/*   Updated: 2018/01/18 14:37:52 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		delimiteur(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\0')
		return (1);
	return (0);
}

char			*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	int		k;
	char	*ret;

	if (s)
	{
		i = 0;
		k = 0;
		j = ft_strlen(s);
		if (!(*s))
			return ((char*)s);
		while (delimiteur(s[i]))
			i++;
		while (delimiteur(s[j]))
			j--;
		if (i > j)
			return (ft_strnew(0));
		if (!(ret = (char*)malloc(sizeof(char) * (j - i) + 2)))
			return (NULL);
		while (i <= j)
			ret[k++] = s[i++];
		ret[k] = '\0';
	}
	return ((s) ? ret : NULL);
}

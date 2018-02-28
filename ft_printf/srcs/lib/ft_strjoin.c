/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 03:17:37 by ddinaut           #+#    #+#             */
/*   Updated: 2017/11/24 11:05:24 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static char			*ft_ret(char const *s1, char const *s2)
{
	if (s1 == NULL)
		return (ft_strdup(s2));
	else
		return (ft_strdup(s1));
}

char				*ft_strjoin(char const *s1, char const *s2)
{
	char			*join;
	unsigned int	i;
	unsigned int	a;

	if (s1 == NULL || s2 == NULL)
		return (ft_ret(s1, s2));
	a = ft_strlen(s1);
	if (!(join = (char*)malloc(sizeof(char) * (a + ft_strlen(s2) + 1))))
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		join[i] = s1[i];
	i = -1;
	while (s2[++i] != '\0')
		join[a + i] = s2[i];
	join[a + i] = '\0';
	return (join);
}

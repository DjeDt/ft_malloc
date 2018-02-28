/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 20:13:23 by ddinaut           #+#    #+#             */
/*   Updated: 2018/01/18 14:35:55 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	ft_strdup :
**	-> returns a pointer to a new string which is a duplicate of the string s1
*/

char	*ft_strdup(const char *s1)
{
	char	*ret;
	size_t	i;

	i = -1;
	if (!(ret = (char*)malloc(sizeof(char) * ft_strlen(s1) + 1)))
		return (NULL);
	while (s1[++i] != '\0')
		ret[i] = s1[i];
	ret[i] = '\0';
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 20:14:40 by ddinaut           #+#    #+#             */
/*   Updated: 2016/11/16 19:50:16 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	i;
	char	*ret;
	char	*str;

	i = 0;
	ret = s1;
	str = (char*)s2;
	while (*ret != '\0')
		ret++;
	while ((*str != '\0') && (i < n))
	{
		*ret = *str;
		i++;
		ret++;
		str++;
	}
	*ret = '\0';
	return (s1);
}

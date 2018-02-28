/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 15:58:59 by ddinaut           #+#    #+#             */
/*   Updated: 2018/01/18 14:36:44 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	size_t	count;
	char	*ret;

	count = 0;
	if (ft_strlen(src) < n)
		ret = (char*)malloc(sizeof(char) * ft_strlen(src) + 1);
	else
		ret = malloc(sizeof(char) * n + 1);
	if (ret == NULL)
		return (NULL);
	while (src[count] != '\0' && count < n)
	{
		ret[count] = src[count];
		count++;
	}
	ret[count] = '\0';
	return (ret);
}

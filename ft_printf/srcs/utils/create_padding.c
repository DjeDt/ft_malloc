/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_padding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 12:08:28 by ddinaut           #+#    #+#             */
/*   Updated: 2017/12/15 12:10:55 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*create_padding(int size, char c)
{
	int		count;
	char	*ret;

	count = 0;
	if (size < 1)
		return (NULL);
	if (!(ret = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (count < size)
		ret[count++] = c;
	ret[count] = '\0';
	return (ret);
}

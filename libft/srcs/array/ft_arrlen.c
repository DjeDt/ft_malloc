/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 19:13:41 by ddinaut           #+#    #+#             */
/*   Updated: 2017/05/11 19:26:24 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_arrlen(char **array)
{
	size_t count;

	count = 0;
	if (array == NULL)
		return (0);
	while (array[count] != NULL)
		count++;
	return (count);
}

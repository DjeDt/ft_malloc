/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 17:02:18 by ddinaut           #+#    #+#             */
/*   Updated: 2017/04/20 15:07:46 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strnlen(const char *str, char c)
{
	size_t count;

	count = 0;
	if (str == NULL)
		return (0);
	while ((str[count] != '\0') && (str[count] != c))
		count++;
	return (count);
}

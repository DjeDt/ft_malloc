/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 16:12:52 by ddinaut           #+#    #+#             */
/*   Updated: 2017/05/15 16:13:01 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_char(const char *str, const char c)
{
	int ret;
	int count;

	ret = 0;
	count = -1;
	if (str == NULL)
		return (-1);
	while (str[++count] != '\0')
		str[count] == c ? ret++ : 0;
	return (ret);
}

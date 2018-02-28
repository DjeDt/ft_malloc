/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 19:29:32 by ddinaut           #+#    #+#             */
/*   Updated: 2018/01/18 14:33:48 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init(int *neg, int *len, unsigned int *val, char **ret)
{
	(*neg) = 0;
	(*len) = 0;
	(*val) = 0;
	(*ret) = NULL;
}

void	is_neg(int base, int *neg, unsigned int *val, int value)
{
	if (base < 2 && base > 16)
	{
		(*val) = value * (-1);
		(*neg) = 1;
	}
	else if (value < 0)
		(*val) = value * (-1);
	else
		(*val) = value;
}

int		get_len(unsigned int val, int base)
{
	int len;

	len = 1;
	while (val /= base)
		len++;
	return (len);
}

char	*ft_itoa_base(int value, int base)
{
	int				len;
	int				neg;
	unsigned int	val;
	char			*ret;
	char			*str;

	str = "0123456789ABCDEF";
	init(&neg, &len, &val, &ret);
	is_neg(base, &neg, &val, value);
	len = get_len(val, base) + neg;
	if (!(ret = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ret[len] = '\0';
	while (len--)
	{
		ret[len] = str[val % base];
		val /= base;
	}
	if (neg == 1)
		ret[0] = '-';
	return (ret);
}

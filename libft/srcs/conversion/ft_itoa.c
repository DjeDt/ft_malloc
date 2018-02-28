/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 20:39:33 by ddinaut           #+#    #+#             */
/*   Updated: 2017/03/14 17:26:51 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		nb_nbr(int n)
{
	int i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char			*ft_itoa(int n)
{
	int				j;
	int				sig;
	char			*ret;
	unsigned int	nbr;

	sig = 0;
	j = nb_nbr(n);
	nbr = n;
	if (n < 0)
	{
		sig = 1;
		nbr = -n;
	}
	if (!(ret = (char*)malloc(sizeof(char) * j + sig + 1)))
		return (NULL);
	ret[j + sig] = '\0';
	while (j-- > 0)
	{
		ret[j + sig] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (sig == 1)
		ret[0] = '-';
	return (ret);
}

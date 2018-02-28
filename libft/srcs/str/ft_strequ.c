/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 02:47:37 by ddinaut           #+#    #+#             */
/*   Updated: 2016/11/16 19:48:37 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	ft_strequ :
**	-> compare s1 and s2, return 1 if strings are the same, 0 if not
*/

int		ft_strequ(char const *s1, char const *s2)
{
	size_t i;

	i = 0;
	if (s1 && s2)
	{
		while (s1[i] || s2[i])
		{
			if (s1[i] != s2[i])
				return (0);
			i++;
		}
		return (1);
	}
	else
		return (0);
}

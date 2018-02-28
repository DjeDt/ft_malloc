/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 20:11:51 by ddinaut           #+#    #+#             */
/*   Updated: 2016/11/16 19:47:49 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	ft_strcmp :
**	-> Returns an integer less than, equal to, greater than zero if s1 is found,
**	   respectively, to be less than, to match, or be greater than s2
*/

int		ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (((unsigned char)s1[i] == (unsigned char)s2[i]) && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

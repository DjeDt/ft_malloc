/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 19:59:58 by ddinaut           #+#    #+#             */
/*   Updated: 2017/09/25 16:32:04 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	ft_bzero :
**	-> ft_bzero() erase n bytes of the memory pointed by s by writting '\0'
*/

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*tmp;

	tmp = s;
	while (n--)
		tmp[n] = '\0';
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 02:03:56 by ddinaut           #+#    #+#             */
/*   Updated: 2017/12/04 16:35:06 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
**	ft_strdel :
**	-> free memory pointed by as and put it at NULL
*/

void	ft_strdel(char **as)
{
	if ((as != NULL) && ((*as) != NULL))
	{
		free(*as);
		(*as) = NULL;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_sign.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 14:44:57 by ddinaut           #+#    #+#             */
/*   Updated: 2017/12/28 14:45:09 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	move_sign(char **to_add)
{
	int		count;
	int		count2;

	count = 0;
	count2 = 0;
	while ((*to_add)[count] != '\0' && (*to_add)[count] != '-')
	{
		if ((*to_add)[count2] != '0')
			count2++;
		count++;
	}
	(*to_add)[count] = (*to_add)[count2];
	(*to_add)[count2] = '-';
}

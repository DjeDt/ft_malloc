/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 17:11:37 by ddinaut           #+#    #+#             */
/*   Updated: 2017/11/24 09:27:52 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	nbr_len(unsigned long long i, int base)
{
	int len;

	len = 1;
	while (i /= base)
		len++;
	return (len);
}

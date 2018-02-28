/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 16:44:44 by ddinaut           #+#    #+#             */
/*   Updated: 2017/09/25 17:21:17 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		compare_node(void *leftp, void *rightp)
{
	int *left;
	int *right;

	left = (int*)leftp;
	right = (int*)rightp;
	if (left < right)
		return (-1);
	else if (left > right)
		return (1);
	else
		return (0);
}

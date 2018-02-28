/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 16:48:03 by ddinaut           #+#    #+#             */
/*   Updated: 2017/06/12 16:48:04 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		count_node(t_btree *tr)
{
	int	count;

	if (tr == NULL)
		return (0);
	count = 0;
	return (count_node(tr->left) + count_node(tr->right) + (++count));
}

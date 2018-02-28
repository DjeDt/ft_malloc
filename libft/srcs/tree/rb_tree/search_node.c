/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 17:36:42 by ddinaut           #+#    #+#             */
/*   Updated: 2017/09/25 17:36:42 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_rbtree	*search_node(t_rbtree **root, void *value, compare_func compare)
{
	int			result;
	t_rbtree	*n;

	n = (*root);
	while (n != NULL)
	{
		result = compare(value, n->data);
		if (result == 0)
			return (n);
		else if (result < 0)
			n = n->left;
		else
			n = n->right;
	}
	return (n);
}

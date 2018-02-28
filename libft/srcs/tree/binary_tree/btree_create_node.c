/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:56:34 by ddinaut           #+#    #+#             */
/*   Updated: 2017/06/15 18:20:46 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_btree		*btree_create_node(void *item)
{
	t_btree *new;

	if (!(new = (t_btree*)malloc(sizeof(t_btree))))
		return (NULL);
	else
	{
		new->left = NULL;
		new->right = NULL;
		new->root = NULL;
		new->item = item;
	}
	return (new);
}

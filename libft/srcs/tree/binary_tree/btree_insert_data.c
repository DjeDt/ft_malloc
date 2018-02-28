/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 15:12:47 by ddinaut           #+#    #+#             */
/*   Updated: 2017/09/25 16:43:26 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			btree_insert_data(t_btree **root, void *item, int (*cmpf)
								(void *, void *))
{
	if (item == NULL)
		return ;
	if ((*root) == NULL)
		(*root) = btree_create_node(item);
	else if ((*cmpf)(item, (*root)->item) < 0)
	{
		btree_insert_data(&(*root)->left, item, cmpf);
		(*root)->left->root = (*root);
	}
	else
	{
		btree_insert_data(&(*root)->right, item, cmpf);
		(*root)->right->root = (*root);
	}
}

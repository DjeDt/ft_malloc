/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 17:34:34 by ddinaut           #+#    #+#             */
/*   Updated: 2017/09/25 17:35:22 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_rbtree	*create_node(void *data, t_rbtree *parent)
{
	t_rbtree *new;

	if (!(new = (t_rbtree*)malloc(sizeof(t_rbtree) * 1)))
		return (NULL);
	new->hash = 0;
	new->data = data;
	new->color = BLACK;
	new->left = NULL;
	new->right = NULL;
	new->parent = parent;
	return (new);
}

void		insert_node2(t_rbtree **root, t_rbtree *parent, \
						void *data, compare_func compare)
{
	if (data == NULL)
		return ;
	if ((*root) == NULL)
	{
		(*root) = create_node(data, parent);
		insert_case1((*root));
	}
	else if (compare(data, (*root)->data) < 0)
	{
		insert_node2(&(*root)->left, (*root), data, compare);
		(*root)->left->parent = (*root);
	}
	else
	{
		insert_node2(&(*root)->right, (*root), data, compare);
		(*root)->right->parent = (*root);
	}
}

void		insert_node(t_rbtree **root, void *data, compare_func compare)
{
	if (data == NULL)
		return ;
	if (*root == NULL)
	{
		(*root) = create_node(data, NULL);
		insert_case1((*root));
	}
	else if (compare(data, (*root)->data) < 0)
	{
		insert_node2(&(*root)->left, (*root), data, compare);
		(*root)->left->parent = (*root);
	}
	else
	{
		insert_node2(&(*root)->right, (*root), data, compare);
		(*root)->right->parent = (*root);
	}
}

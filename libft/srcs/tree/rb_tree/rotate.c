/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 17:36:22 by ddinaut           #+#    #+#             */
/*   Updated: 2017/09/25 17:36:28 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	rotate_left(t_rbtree *n, t_rbtree *g)
{
	t_rbtree *saved_p;
	t_rbtree *saved_left_n;

	saved_p = g->left;
	saved_left_n = n->left;
	g->left = n;
	n->left = saved_p;
	saved_p->right = saved_left_n;
	return ;
}

void	rotate_right(t_rbtree *n, t_rbtree *g)
{
	t_rbtree *saved_p;
	t_rbtree *saved_right_n;

	saved_p = g->right;
	saved_right_n = n->right;
	g->right = n;
	n->right = saved_p;
	saved_p->left = saved_right_n;
	return ;
}

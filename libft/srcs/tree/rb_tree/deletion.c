/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deletion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 17:23:33 by ddinaut           #+#    #+#             */
/*   Updated: 2017/09/25 17:23:33 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	delete_case1(t_rbtree *n)
{
	if (n->parent != NULL)
		delete_case2(n);
}

void	delete_case2(t_rbtree *n)
{
	t_rbtree *sib;
	t_rbtree *gp;

	if (!(sib = sibling(n)))
		return ;
	if (sib->color == RED)
	{
		gp = grandparent(n);
		n->parent->color = RED;
		sib->color = BLACK;
		if (n == n->parent->left)
			rotate_left(n->parent, gp);
		else
			rotate_right(n->parent, gp);
	}
	delete_case3(n);
}

void	delete_case3(t_rbtree *n)
{
	t_rbtree *sib;

	if (!(sib = sibling(n)))
		return ;
	if ((n->parent->color == BLACK) &&
		(sib->color == BLACK) &&
		(sib->left->color == BLACK) &&
		(sib->right->color == BLACK))
	{
		sib->color = RED;
		delete_case1(n->parent);
	}
	else
		delete_case4(n);
}

void	delete_case4(t_rbtree *n)
{
	t_rbtree *sib;

	if (!(sib = sibling(n)))
		return ;
	if ((n->parent->color == RED) &&
		(sib->color == BLACK) &&
		(sib->left->color == BLACK) &&
		(sib->right->color == BLACK))
	{
		sib->color = RED;
		n->parent->color = BLACK;
	}
	else
		delete_case5(n);
}

void	delete_case5(t_rbtree *n)
{
	t_rbtree *sib;
	t_rbtree *gp;

	if (!(sib = sibling(n)))
		return ;
	if (!(gp = grandparent(n)))
		return ;
	if (sib->color == BLACK)
	{
		if ((n == n->parent->left) &&
			(sib->right->color == BLACK) &&
			(sib->left->color == RED))
		{
			sib->color = RED;
			sib->left->color = BLACK;
			rotate_right(sib, gp);
		}
		else if ((n == n->parent->right) &&
				(sib->left->color == BLACK) &&
				(sib->right->color == RED))
		{
			sib->color = RED;
			sib->right->color = BLACK;
			rotate_left(sib, gp);
		}
	}
	delete_case6(n);
}

void	delete_case6(t_rbtree *n)
{
	t_rbtree *sib;
	t_rbtree *gp;

	if (!(sib = sibling(n)))
		return ;
	gp = grandparent(n);
	sib->color = n->parent->color;
	n->parent->color = BLACK;
	if (n == n->parent->left)
	{
		sib->right->color = BLACK;
		rotate_left(n->parent, gp);
	}
	else
	{
		sib->left->color = BLACK;
		rotate_right(n->parent, gp);
	}
}
